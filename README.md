
# DeviceSpeak IoT Data Collection Project

## Project Overview

This project is designed for collecting, compressing, and storing IoT data from various devices in batches. The system collects device information, compresses it using the Zstandard compression algorithm, and stores it in a binary file format. Data can later be retrieved and transmitted when network connectivity is restored.

## Project Structure

- **collect_data.c**: The main source file responsible for initializing data collection, adding data to batches, compressing data, and storing it in a binary file.
- **collect_data.h**: Header file containing data structures and function prototypes for managing data collection, compression, and storage.
- **offline_data.bin**: A file used to store compressed data when the network is unavailable.

## File Descriptions

### `collect_data.c`
This file includes:
- **Data Collection**: Functions to gather device metrics (e.g., IMEI, ICCID, signal strength).
- **Batching**: Collects data into batches (size defined by `BATCH_SIZE`) before compression.
- **Compression**: Utilizes Zstandard to compress data.
- **Storage**: Saves compressed data to `offline_data.bin`.

### `collect_data.h`
Contains:
- **PBDATA_t**: Data structure defining all fields collected from the device (e.g., IMEI, signal strength, location).
- **Function Prototypes**: Includes initialization, data collection, batch storage, and JSON conversion functions.

## Compilation and Setup

### Requirements
- **Zstandard Library**: Ensure `libzstd` is installed for data compression.
  - For Linux: `sudo apt install libzstd-dev`
  - For Windows: Download and set up `zstd` from https://facebook.github.io/zstd/.

### Compilation
Compile using `gcc`:
```bash
gcc -o device_data_collect collect_data.c -lzstd
```

### Run the Program
Execute the compiled program:
```bash
./device_data_collect
```

## Code Documentation

### Functions

- `void collect_init()`: Initializes the data collection process and prepares any hardware or settings.
- `bool collect_Data(char* buf, uint8_t** dbuf, int16_t* len)`: Collects data from the device, stores it in a batch, and returns a JSON representation.
- `int compress_data(const unsigned char *source, size_t source_len, unsigned char **dest, size_t *dest_len)`: Compresses data using Zstandard.
- `void store_data_batch()`: Compresses and stores data batch into `offline_data.bin`.
- `void add_data_to_batch(PBDATA_t *data)`: Adds data to a batch and stores it when the batch is full.

## How to Use

1. **Initialize Data Collection**: Run `collect_init()` to prepare the system.
2. **Collect Data**: Call `collect_Data()` to gather data and add it to the batch.
3. **Batch Processing**: Data is batched and stored once it reaches the batch size limit.
4. **Transmission**: When network connectivity is restored, retrieve and transmit data from `offline_data.bin`.



**END OF README**
