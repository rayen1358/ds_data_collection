
Device Data Collection and Compression System
=============================================

This project is a C-based system that collects device telemetry data, batches it, compresses it using the Zstandard (ZSTD) algorithm, and stores it for later transmission. The system can also format the collected data into JSON for network transmission or other use cases.

Project Structure
-----------------

- **collect_data.c**: Implements data collection, batching, compression, and storage functions.
- **collect_data.h**: Defines data structures and function prototypes for data collection.

Key Components
--------------

### Data Structure (PBDATA_t)
The `PBDATA_t` struct defines the telemetry data fields collected from the device, including:

- **Device Identifiers**: `imei`, `iccid`
- **Status Indicators**: `GPRSsignal`, `DeviceEtat`, `DeviceBattery`, `IgnitionStatus`, `DIN1`, `DOUT0`, `DOUT1`
- **Location Data**: `latitude`, `longitude`, `speed`, `DataTime`, `LastTime`
- **Sensors Data**: `ax`, `ay`, `az`, `gx`, `gy`, `gz` (acceleration and gyroscope arrays)
- **Other**: `satTrack`, `hourMeter`, `VehicleEtat`, `VehicleBattery`, `distance`, `stationary`

### Function Descriptions

1. **collect_init**: Initializes the data collection system. This could involve hardware setups or resetting relevant settings.
2. **collect_Data**: Collects and formats data into a JSON string. Populates a buffer with JSON data for transmission.
3. **add_data_to_batch**: Adds data to the batch buffer for compression. If the batch reaches the `BATCH_SIZE`, it triggers storage of the compressed batch.
4. **store_data_batch**: Compresses the batched data using Zstandard and writes it to a file (`offline_data.bin`) for offline storage.
5. **compress_data**: Compresses raw data using the Zstandard library with a specified compression level.
6. **edatatojson**: Converts collected data to JSON format for use in communication or logging.

### Constants

- **BATCH_SIZE**: Number of `PBDATA_t` records to batch before compression and storage.

Installation
------------

Ensure you have the Zstandard library (`libzstd`) installed to support data compression.

### Dependencies

- **Zstandard (ZSTD)**: Required for data compression.
- **Standard Libraries**: `<stdio.h>`, `<stdlib.h>`, `<string.h>`, `<stdint.h>`, and `<stdbool.h>`

Usage
-----

### Initialization

1. **Compile** the code using your C compiler.
2. **Run** the `main()` function (if uncommented) to initialize data collection.

### Data Collection and Compression

1. **collect_Data**: Gathers data in JSON format and prepares it for transmission.
2. **add_data_to_batch**: Adds data to a batch buffer and triggers storage if the buffer is full.
3. **store_data_batch**: Compresses and saves batched data for offline storage.

### Example Workflow

```c
collect_init();  // Initialize data collection

// Collect data and convert it to JSON
uint8_t *data_buffer;
int16_t data_length;
if (collect_Data(NULL, &data_buffer, &data_length)) {
    printf("Collected data: %s\n", data_buffer);
    free(data_buffer);  // Free allocated memory
} else {
    printf("Failed to collect data.\n");
}
```

### File Storage

Compressed data is stored in `offline_data.bin`. Each batch is compressed and appended to this file, allowing for efficient offline data storage.

Error Handling
--------------

- **Memory Allocation**: Functions allocate memory as needed. Ensure sufficient memory is available.
- **Compression Errors**: If compression fails, the system handles the error and cleans up allocated resources.

-------
