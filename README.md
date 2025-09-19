# ESP32 WiFi Configuration

A simple ESP32 WiFi connection project with secure credential management and LED signal strength indicator.

## Features

- **Secure WiFi Configuration**: Credentials stored in separate file (gitignored)
- **Auto-reconnection**: Automatically reconnects if WiFi drops
- **Signal Strength LED**: Built-in LED shows WiFi signal strength via blink patterns
- **Serial Monitoring**: Real-time connection status and debugging
- **Arduino IDE Compatible**: Easy to use with Arduino IDE

## Prerequisites

- [Arduino IDE](https://www.arduino.cc/en/software) installed
- ESP32 board package installed in Arduino IDE
- ESP32C3 development board

## Installation

### 1. Install Arduino IDE

Download and install Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software)

### 2. Install ESP32 Board Package

1. Open Arduino IDE
2. Go to **File** → **Preferences**
3. Add this URL to **Additional Board Manager URLs**:

   ```plaintext
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```

4. Go to **Tools** → **Board** → **Boards Manager**
5. Search for "ESP32" and install "ESP32 by Espressif Systems"

### 3. Open Project in Arduino IDE

1. Open Arduino IDE
2. Go to **File** → **Open**
3. Navigate to this project folder
4. Open `esp32-wifi-config/esp32-wifi-config.ino`

### 4. Configure Board Settings

1. Go to **Tools** → **Board** → **ESP32 Arduino** → **ESP32C3 Dev Module**
2. Set **CPU Frequency** to `80MHz`
3. Set **Flash Mode** to `DIO`
4. Set **Partition Scheme** to `Default 4MB with spiffs`
5. Set **Upload Speed** to `115200`
6. Set **USB CDC On Boot** to `Enabled`

## WiFi Configuration

### WiFi Credentials

1. Copy `wifi_config_template.h` to `wifi_config.h`:

   ```bash
   cp esp32-wifi-config/wifi_config_template.h esp32-wifi-config/wifi_config.h
   ```

2. Edit `esp32-wifi-config/wifi_config.h` with your WiFi credentials:

   ```cpp
   const char* WIFI_SSID = "YourWiFiNetwork";
   const char* WIFI_PASSWORD = "YourWiFiPassword";
   ```

**Note**: `wifi_config.h` is gitignored for security.

## Usage

### 1. Connect ESP32

- Connect your ESP32C3 to your computer via USB
- Select the correct COM port in Arduino IDE

### 2. Upload Code

- Click the **Upload** button (→) in Arduino IDE
- Wait for upload to complete

### 3. Monitor Serial Output

- Open **Tools** → **Serial Monitor**
- Set baud rate to `115200`
- Watch for connection status and signal strength

## LED Signal Strength Indicator

The built-in LED shows WiFi signal strength:

- **Fast blink (100ms)**: Strong signal (-30 to -50 dBm)
- **Medium blink (500ms)**: Medium signal (-50 to -70 dBm)
- **Slow blink (1000ms)**: Weak signal (below -70 dBm)
- **LED off**: No WiFi connection

## Project Structure

```plaintext
esp32-wifi-config-cpp/
├── esp32-wifi-config/
│   ├── esp32-wifi-config.ino    # Main Arduino sketch
│   ├── wifi_config.h            # WiFi credentials (gitignored)
│   └── wifi_config_template.h   # Credentials template
├── .gitignore                   # Git ignore rules
└── README.md                    # This file
```

## Troubleshooting

### Common Issues

#### 1. Board not found

- Check USB connection
- Install correct drivers
- Verify COM port selection

#### 2. Upload fails

- Press and hold BOOT button while uploading
- Check board settings (CPU frequency, flash mode)
- Try different USB cable

#### 3. WiFi connection fails

- Verify credentials in `wifi_config.h`
- Check WiFi network availability
- Ensure 2.4GHz network (ESP32 doesn't support 5GHz)

#### 4. Serial monitor shows boot loop

- Check board settings, especially CPU frequency (must be 80MHz for ESP32C3)
- Verify flash mode is set to DIO
- Try different partition scheme

#### 5. No serial output

- Set **USB CDC On Boot** to `Enabled`
- Check baud rate (115200)
- Try different COM port

### Board Settings for ESP32C3

- **Board**: ESP32C3 Dev Module
- **CPU Frequency**: 80MHz
- **Flash Mode**: DIO
- **Flash Size**: 4MB
- **Partition Scheme**: Default 4MB with spiffs
- **Upload Speed**: 115200
- **USB CDC On Boot**: Enabled

## Security Notes

- WiFi credentials are stored in `wifi_config.h` which is gitignored
- Never commit real credentials to version control
- Use the template file for new deployments
- Change default credentials before production use

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
