import tkinter as tk
from tkinter import ttk, messagebox
import serial
import serial.tools.list_ports
import struct

ser = None

# ========= SERIAL PORT =========
def list_serial_ports():
    ports = serial.tools.list_ports.comports()
    return [port.device for port in ports]

def refresh_ports():
    ports = list_serial_ports()
    port_combo['values'] = ports
    if ports:
        port_combo.current(0)

def connect_serial():
    global ser
    try:
        ser = serial.Serial(port_combo.get(), 9600, timeout=1)
        status_label.config(text="Connected", foreground="green")
    except Exception as e:
        messagebox.showerror("Error", str(e))

# ========= FRAME BUILD & SEND =========
def build_frame(cmd, payload_bytes):
    length = len(payload_bytes)
    checksum = cmd + length + sum(payload_bytes)
    checksum &= 0xFFFFFFFF
    frame = struct.pack("<H", cmd)
    frame += struct.pack("<H", length)
    frame += bytes(payload_bytes)
    frame += struct.pack("<I", checksum)
    return frame

def send_command(cmd, payload=[]):
    if ser and ser.is_open:
        frame = build_frame(cmd, payload)
        ser.write(frame)
        print("Sent:", frame.hex())
    else:
        messagebox.showwarning("Warning", "Serial not connected")

# ========= COMMAND CALLBACKS =========
def start_pwm():
    send_command(0)

def stop_pwm():
    send_command(1)

def set_frequency():
    try:
        freq = int(freq_entry.get())
        send_command(2, [freq & 0xFF, (freq >> 8) & 0xFF])
    except ValueError:
        messagebox.showwarning("Input Error", "Enter a valid frequency")

def set_duty():
    try:
        duty = int(duty_entry.get())
        if 0 <= duty <= 100:
            send_command(3, [duty])
        else:
            messagebox.showwarning("Input Error", "Duty must be 0-100")
    except ValueError:
        messagebox.showwarning("Input Error", "Enter a valid duty")

# ========= MEASURE =========
def measure():
    send_command(4)
    root.after(300, receive_measure)  # attend que STM32 envoie la mesure

def receive_measure():
    try:
        if ser and ser.in_waiting:
            line = ser.readline().decode().strip()
            print("Received:", line)

            # Extraction simple
            if "Freq:" in line and "Duty:" in line:
                parts = line.replace(",", "").split()
                freq = parts[1]
                duty = parts[4]

                freq_label.config(text=f"{freq} Hz")
                duty_label.config(text=f"{duty} %")

    except Exception as e:
        print("Receive error:", e)
# ========= TKINTER UI =========
root = tk.Tk()
root.title("STM32 PWM Controller")
root.geometry("500x600")
root.minsize(500, 600)

style = ttk.Style()
style.theme_use("clam")

# Configuration expansion
root.columnconfigure(0, weight=1)
root.rowconfigure(0, weight=1)

main_frame = ttk.Frame(root, padding=20)
main_frame.grid(row=0, column=0, sticky="nsew")

main_frame.columnconfigure(0, weight=1)
main_frame.columnconfigure(1, weight=1)

# ================= SERIAL =================
serial_frame = ttk.LabelFrame(main_frame, text="Serial Connection", padding=15)
serial_frame.grid(row=0, column=0, columnspan=2, pady=10, sticky="ew")

serial_frame.columnconfigure(0, weight=1)

port_combo = ttk.Combobox(serial_frame)
port_combo.grid(row=0, column=0, padx=5, pady=5, sticky="ew")

ttk.Button(serial_frame, text="Refresh", command=refresh_ports)\
    .grid(row=0, column=1, padx=5)

ttk.Button(serial_frame, text="Connect", command=connect_serial)\
    .grid(row=1, column=0, padx=5, pady=5, sticky="ew")

status_label = ttk.Label(serial_frame, text="Disconnected", foreground="red")
status_label.grid(row=1, column=1, padx=5)

# ================= PWM CONTROL =================
control_frame = ttk.LabelFrame(main_frame, text="PWM Control", padding=15)
control_frame.grid(row=1, column=0, columnspan=2, pady=10, sticky="ew")

control_frame.columnconfigure(0, weight=1)

ttk.Button(control_frame, text="START PWM", command=start_pwm)\
    .grid(row=0, column=0, pady=5, sticky="ew")

ttk.Button(control_frame, text="STOP PWM", command=stop_pwm)\
    .grid(row=1, column=0, pady=5, sticky="ew")

ttk.Label(control_frame, text="Frequency (Hz):")\
    .grid(row=2, column=0, sticky="w")

freq_entry = ttk.Entry(control_frame)
freq_entry.grid(row=3, column=0, pady=5, sticky="ew")

ttk.Button(control_frame, text="Set Frequency", command=set_frequency)\
    .grid(row=4, column=0, pady=5, sticky="ew")

ttk.Label(control_frame, text="Duty Cycle (%)")\
    .grid(row=5, column=0, sticky="w")

duty_entry = ttk.Entry(control_frame)
duty_entry.grid(row=6, column=0, pady=5, sticky="ew")

ttk.Button(control_frame, text="Set Duty", command=set_duty)\
    .grid(row=7, column=0, pady=5, sticky="ew")

# ================= MEASURE =================
measure_frame = ttk.LabelFrame(main_frame, text="Measured Signal", padding=20)
measure_frame.grid(row=2, column=0, columnspan=2, pady=20, sticky="nsew")

measure_frame.columnconfigure(0, weight=1)

freq_label = ttk.Label(
    measure_frame,
    text="0.00 Hz",
    font=("Arial", 28, "bold")
)
freq_label.grid(row=0, column=0, pady=15)

duty_label = ttk.Label(
    measure_frame,
    text="0.00 %",
    font=("Arial", 28, "bold")
)
duty_label.grid(row=1, column=0, pady=15)

duty_bar = ttk.Progressbar(
    measure_frame,
    orient="horizontal",
    length=350,
    mode="determinate",
    maximum=100
)
duty_bar.grid(row=2, column=0, pady=10)

ttk.Button(main_frame, text="Measure", command=measure)\
    .grid(row=3, column=0, columnspan=2, pady=10, sticky="ew")

refresh_ports()
root.mainloop()