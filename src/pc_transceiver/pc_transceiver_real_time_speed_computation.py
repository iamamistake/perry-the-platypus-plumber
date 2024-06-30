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
REAL_TIME_PROCESSING_WINDOW_DURATION = 0.5

pc_transceiver = serial.Serial(PORT, BAUD_RATE)
time.sleep(POST_INITIALIZATION_WAIT_TIME)
print("COM PORT INITIALIZED\n")

real_time_processing_chunk_count = 0

print("Transmitting Text Data...\n")
start_time = time.perf_counter()
for index in range(TEXT_LENGTH):
    pc_transceiver.write(TEXT[index].encode("utf-8"))
    real_time_processing_chunk_count += 1
    elapsed_time = time.perf_counter() - start_time
    if (elapsed_time >= REAL_TIME_PROCESSING_WINDOW_DURATION):
        if (platform.system() == "Windows"):
            os.system("cls")
        elif (platform.system() == "Linux"):
            os.system("clear")
        print(f"Transmission Speed: {(DATA_FRAME_BITS_COUNT * real_time_processing_chunk_count)/elapsed_time} bits/second")
        start_time = time.perf_counter()
        real_time_processing_chunk_count = 0

received_data_buffer = ""
received_data_count = 0

print("Receiving Text Data...\n")
real_time_processing_chunk_count = 0
start_time = time.perf_counter()

while True:
    received_data_buffer += pc_transceiver.read(1).decode("utf-8")

    real_time_processing_chunk_count += 1
    received_data_count += 1

    elapsed_time = time.perf_counter() - start_time

    if ((elapsed_time >= REAL_TIME_PROCESSING_WINDOW_DURATION) or (received_data_count == TEXT_LENGTH)):
        if (platform.system() == "Windows"):
            os.system("cls")
        elif (platform.system() == "Linux"):
            os.system("clear")
        if (received_data_count != TEXT_LENGTH):
            print(f"Reception Speed: {(DATA_FRAME_BITS_COUNT * real_time_processing_chunk_count)/elapsed_time} bits/second\n", flush = True)
        print(received_data_buffer, end="", flush = True)
        start_time = time.perf_counter()
        real_time_processing_chunk_count = 0
        if (received_data_count == TEXT_LENGTH):
            exit()