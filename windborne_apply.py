# WindBorne Sensors Intern — ESP32 POST Request
#
# Flash this to your ESP32 running MicroPython.
# Steps:
#   1. Install MicroPython on your ESP32 (if not already)
#   2. Copy this file to the ESP32 as main.py (or run via REPL)
#   3. Update WIFI_SSID below if needed
#   4. The script connects to WiFi and sends the POST request

import network
import urequests
import ujson
import time

# ----- CONFIG -----
WIFI_SSID = "Columbia University"
WIFI_PASSWORD = ""  # Open network

ENDPOINT = "https://windbornesystems.com/career_applications.json"

PAYLOAD = {
    "career_application": {
        "name": "Shlok Desai",
        "email": "sbd2150@columbia.edu",
        "role": "Sensors Intern",
        "notes": (
            "Nairobi, Kenya. WindBorne's current launch sites (Seoul, Maui) cover "
            "the northern Pacific well, but sub-Saharan Africa remains one of the "
            "largest radiosonde deserts on the planet — the WMO's GUAN network has "
            "massive gaps across East Africa. A Nairobi site would fill critical "
            "data voids over the Indian Ocean and the African interior, directly "
            "improving forecasts for monsoon onset, tropical cyclone genesis in the "
            "southwestern Indian Ocean, and agricultural planning for hundreds of "
            "millions of people who depend on rain-fed farming. Plus, it's a place "
            "I've always wanted to visit — the Great Rift Valley, Maasai Mara, and "
            "Mount Kenya are on my bucket list. "
            "(P.S. This POST request was sent from an ESP32 on my desk at Columbia.)"
        ),
        "submission_url": "https://desaishlok.github.io/windborne.html",
        "resume_url": "https://desaishlok.github.io/ShlokDesai_Resume.pdf"
    }
}


def connect_wifi():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)

    if wlan.isconnected():
        print("[OK] Already connected:", wlan.ifconfig())
        return True

    print("[..] Connecting to", WIFI_SSID)
    wlan.connect(WIFI_SSID, WIFI_PASSWORD)

    for _ in range(30):
        if wlan.isconnected():
            print("[OK] Connected:", wlan.ifconfig())
            return True
        time.sleep(1)

    print("[FAIL] Could not connect to WiFi")
    return False


def send_application():
    headers = {"Content-Type": "application/json"}
    body = ujson.dumps(PAYLOAD)

    print("[..] Sending POST to", ENDPOINT)
    try:
        resp = urequests.post(ENDPOINT, data=body, headers=headers)
        print("[>>] Status:", resp.status_code)
        print("[>>] Response:", resp.text)

        if resp.status_code == 200:
            print("\n=== APPLICATION ACCEPTED ===")
        else:
            print("\n=== NOT ACCEPTED — check response above ===")

        resp.close()
    except Exception as e:
        print("[ERR]", e)


def main():
    print("\n--- WindBorne Sensors Intern Application ---")
    print("--- Sent from ESP32 @ Columbia University ---\n")

    if connect_wifi():
        send_application()
    else:
        print("Aborting: no WiFi connection")


main()
