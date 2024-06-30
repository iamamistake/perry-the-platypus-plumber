import serial
import time
import os
import platform

TEXT = "A platypus plumber? A perry the platypus plumber? PERRY THE PLATYPUS!!!!"
TEXT_LENGTH = len(TEXT)
print(f"\nText Length: {TEXT_LENGTH}")

# Set up a proper COM port before proceeding further
if (platform.system() == "Windows"):
    PORT = "COM8"
elif (platform.system() == "Linux"):
    PORT = "/dev/ttyUSB0"
BAUD_RATE = 2400
DATA_FRAME_BITS_COUNT = (1 + 8 + 1)
POST_INITIALIZATION_WAIT_TIME = 2

pc_transceiver = serial.Serial(PORT, BAUD_RATE)
time.sleep(POST_INITIALIZATION_WAIT_TIME)
print("COM PORT INITIALIZED\n")

print("Transmitting Text Data...\n")
start_time = time.perf_counter()
for index in range(TEXT_LENGTH):
    pc_transceiver.write(TEXT[index].encode("utf-8"))

elapsed_time = time.perf_counter() - start_time
print(f"Average Transmission Speed: {(DATA_FRAME_BITS_COUNT * TEXT_LENGTH)/elapsed_time} bits/second\n")

print("Receiving Text Data...\n")
start_time = time.perf_counter()
for _ in range(TEXT_LENGTH):
    data = pc_transceiver.read(1).decode("utf-8")
    print(data, end = "", flush = True)

elapsed_time = time.perf_counter() - start_time
print(f"\n\nAverage Reception Speed: {(DATA_FRAME_BITS_COUNT * TEXT_LENGTH)/elapsed_time} bits/second\n")