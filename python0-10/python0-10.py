import tkinter as tk
from tkinter import font
import paho.mqtt.client as mqtt

# MQTT 브로커 설정
MQTT_BROKER = "broker.emqx.io"
MQTT_PORT = 1883
MQTT_TOPICS = [
    "arduino/led1", "arduino/led2", "arduino/led3", "arduino/led4",
    "arduino/led5", "arduino/led6", "arduino/led7", "arduino/led8",
]

# MQTT 클라이언트 초기화
client = mqtt.Client()

def on_connect(client, userdata, flags, rc):
    """MQTT 연결 콜백 함수"""
    if rc == 0:
        print("MQTT 연결 성공!")
    else:
        print(f"MQTT 연결 실패! 코드: {rc}")

def on_disconnect(client, userdata, rc):
    """MQTT 연결이 끊겼을 때 재연결 시도"""
    print("MQTT 연결 끊김! 재연결 시도...")
    connect_mqtt()

def connect_mqtt():
    """MQTT 브로커에 연결"""
    try:
        client.on_connect = on_connect
        client.on_disconnect = on_disconnect
        client.connect(MQTT_BROKER, MQTT_PORT, 60)
        client.loop_start()
    except Exception as e:
        print(f"MQTT 연결 오류: {e}")

# LED 상태 변경 함수
def toggle_led(index):
    current_state = led_states[index].get()
    new_state = not current_state
    message = "1" if new_state else "0"

    client.publish(MQTT_TOPICS[index], message)
    led_states[index].set(new_state)  # 상태 업데이트
    buttons[index].config(
        text=f"LED {index+1} {'끄기' if new_state else '켜기'}",
        bg="#FF5252" if new_state else "#1976D2"
    )

# GUI 종료 시 MQTT 종료
def on_closing():
    print("프로그램 종료, MQTT 연결 해제...")
    client.loop_stop()
    client.disconnect()
    window.destroy()

# GUI 생성
def create_gui():
    global window, buttons, led_states
    window = tk.Tk()
    window.title("라즈베리파이 MQTT 컨트롤러")
    window.geometry("400x600")
    window.configure(bg="#1E1E1E")

    title_font = font.Font(family="맑은 고딕", size=20, weight="bold")
    button_font = font.Font(family="맑은 고딕", size=14, weight="bold")

    title = tk.Label(window, text="MQTT LED 컨트롤러", font=title_font, bg="#1E1E1E", fg="#4FC3F7")
    title.pack(pady=20)

    buttons = []
    led_states = [tk.BooleanVar(value=False) for _ in range(len(MQTT_TOPICS))]

    for i in range(len(MQTT_TOPICS)):
        btn = tk.Button(
            window, text=f"LED {i+1} 켜기", font=button_font,
            width=20, height=2, bg="#1976D2", fg="#FFFFFF",
            command=lambda idx=i: toggle_led(idx)
        )
        btn.pack(pady=10)
        buttons.append(btn)

    window.protocol("WM_DELETE_WINDOW", on_closing)  # 창 닫기 이벤트 처리
    window.mainloop()

if __name__ == "__main__":
    connect_mqtt()
    create_gui()
