import mido
import threading
import time

def monitor_port(port_name):
    """Monitor MIDI messages from a specific port"""
    try:
        with mido.open_input(port_name) as inport:
            print(f"Monitoring port: {port_name}")
            for msg in inport:
                # Filter out MIDI clock messages (type 'clock')
                if msg.type != 'clock':
                    print(f"[{port_name}] {msg}")
    except Exception as e:
        print(f"Error monitoring port {port_name}: {e}")

def main():
    print("MIDI Monitor - Press Ctrl+C to exit")

    # Get available input ports
    input_ports = mido.get_input_names()

    if not input_ports:
        print("No MIDI input ports available")
        return

    print(f"Found {len(input_ports)} input port(s):")
    for port in input_ports:
        print(f"  - {port}")

    # Start monitoring threads for each port
    threads = []
    for port_name in input_ports:
        thread = threading.Thread(target=monitor_port, args=(port_name,), daemon=True)
        thread.start()
        threads.append(thread)

    try:
        # Keep main thread alive
        while True:
            time.sleep(0.1)
    except KeyboardInterrupt:
        print("\nExiting MIDI monitor...")

if __name__ == "__main__":
    main()
