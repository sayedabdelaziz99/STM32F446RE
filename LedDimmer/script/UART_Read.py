import serial
import csv
import time

# Configure the serial port
serial_port = 'COM3'
baud_rate = 115200
timeout = 1

# Open the serial port
ser = serial.Serial(serial_port, baud_rate, timeout=timeout)

# Create a CSV file and set up a writer
csv_filename = 'serial_data.csv'
with open(csv_filename, 'w', newline='') as csvfile:
    csv_writer = csv.writer(csvfile)

    # Write the CSV header
    csv_writer.writerow(['Data'])

    # Read and record data from the serial port
    try:
        while True:
            data = ser.readline().decode('ascii').strip()
            if data:
                timestamp = time.time()
                print(f'{data}')
                csv_writer.writerow([data])
    except KeyboardInterrupt:
        print('Stopped recording data.')
        ser.close()