#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zstd.h>
#include "collect_data.h"

// Global variable to hold the length of PBDATA_t
uint16_t lenthpbd = sizeof(PBDATA_t);

// Buffer to hold batched data for compression
typedef struct {
    PBDATA_t data[BATCH_SIZE];
    size_t count;
} DataBatch;

DataBatch batch = { .count = 0 };

// Initialize the data collection process
void collect_init() {
    // Initialize any required hardware or settings
    printf("Data collection initialized.\n");
}

// Function to compress data using Zstandard
int compress_data(const unsigned char *source, size_t source_len, unsigned char **dest, size_t *dest_len) {
    // Allocate enough space for the compressed data
    size_t compressed_size = ZSTD_compressBound(source_len);
    *dest = (unsigned char *)malloc(compressed_size);
    if (*dest == NULL) {
        return Z_MEM_ERROR;
    }

    // Compress the data
    compressed_size = ZSTD_compress(*dest, compressed_size, source, source_len, 1); // Level 1 compression
    if (ZSTD_isError(compressed_size)) {
        free(*dest); // Free the allocated buffer on failure
        *dest = NULL;
        return ZSTD_getErrorCode(compressed_size);
    }

    *dest_len = compressed_size; // Set the output length
    return 0; // Success
}

// Store a batch of data
void store_data_batch() {
    // Serialize and compress the entire batch
    size_t raw_size = batch.count * sizeof(PBDATA_t);
    unsigned char *compressed_data = NULL;
    size_t compressed_size = 0;

    if (compress_data((unsigned char *)batch.data, raw_size, &compressed_data, &compressed_size) == 0) {
        // Store the compressed data to a file
        FILE *file = fopen("offline_data.bin", "ab");
        if (file) {
            fwrite(compressed_data, 1, compressed_size, file);
            fclose(file);
            printf("Stored %zu bytes of compressed data.\n", compressed_size);
        }
        free(compressed_data);  // Free the compressed buffer
    }
    batch.count = 0;  // Reset batch count after storing
}

// Function to collect data and store it in a buffer
bool collect_Data(char* buf, uint8_t** dbuf, int16_t* len) {
    // Populate the buffer with data
    PBDATA_t data;

    // Simulate data collection (populate 'data' with real data)
    strcpy((char*)data.imei, "123456789012345"); // Example IMEI
    strcpy((char*)data.iccid, "8901234567890123456"); // Example ICCID
    data.GPRSsignal = 5; // Example signal strength
    data.DeviceEtat = 1; // Example device state
    data.DeviceBattery = 75; // Example battery level
    data.IgnitionStatus = true; // Example ignition status
    // Populate other fields as necessary...

    add_data_to_batch(&data); // Add data to batch

    // Convert PBDATA_t structure to JSON format
    if (dbuf == NULL) {
        *len = 0; // Length is zero if there's no data to send
        return false;
    }

    // Allocate memory for JSON buffer (simple approximation)
    *len = snprintf(NULL, 0, "{\"imei\":\"%s\",\"iccid\":\"%s\",\"GPRSsignal\":%d,\"DeviceEtat\":%d,\"DeviceBattery\":%d}",
                    data.imei, data.iccid, data.GPRSsignal, data.DeviceEtat, data.DeviceBattery);
    *dbuf = (uint8_t*)malloc(*len + 1); // +1 for null terminator
    if (*dbuf == NULL) {
        perror("Failed to allocate memory");
        return false;
    }

    // Populate the buffer with the JSON representation
    snprintf((char *)*dbuf, *len + 1, "{\"imei\":\"%s\",\"iccid\":\"%s\",\"GPRSsignal\":%d,\"DeviceEtat\":%d,\"DeviceBattery\":%d}",
            data.imei, data.iccid, data.GPRSsignal, data.DeviceEtat, data.DeviceBattery);

    return true; // Data collection and conversion successful
}

// Function to convert collected data to JSON
void edatatojson(uint8_t* data, char* buf, uint16_t* len) {
    // Example: Convert raw data buffer to a JSON string
    if (data == NULL || buf == NULL || len == NULL) {
        return; // Invalid input
    }

    // Convert the provided data to JSON format (this is just a placeholder implementation)
    *len = snprintf(buf, *len, "{\"data\":\"%s\"}", data); // Placeholder for actual data
}

// Add data to the batch and store if batch is full
void add_data_to_batch(PBDATA_t *data) {
    if (batch.count < BATCH_SIZE) {
        batch.data[batch.count++] = *data;
    }
    if (batch.count == BATCH_SIZE) {
        store_data_batch();  // Store when batch is full
    }
}

/*int main() {
    collect_init(); // Initialize data collection

    // Buffers for collected data
    uint8_t *data_buffer;
    int16_t data_length;

    // Collect data
    if (collect_Data(NULL, &data_buffer, &data_length)) {
        printf("Collected data: %s\n", data_buffer);
        free(data_buffer); // Free the allocated buffer
    } else {
        printf("Failed to collect data.\n");
    }

    // You can add code to transmit and clear stored data when the network is restored

    return 0;
}
*/