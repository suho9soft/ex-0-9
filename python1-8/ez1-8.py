import tkinter as tk
from tkinter import ttk
import paho.mqtt.client as mqtt
import json  
import pymysql
from datetime import datetime

BROKER_ADDRESS = "broker.emqx.io"
SUBSCRIBE_TOPIC = "arduino/input" 
PUBLISH_TOPIC = "arduino/output"  

def publish_message():
    arduino_info = {
        "name": "arduino",
        "age": 20,
        "gender": "male"
    }
    payload = json.dumps(arduino_info) 
    client.publish(PUBLISH_TOPIC, payload)  
    update_text("Published: Hello from GUI!")

def update_text(message):
    text_box.insert(tk.END, f"{message}\n")
    text_box.see(tk.END)

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe(SUBSCRIBE_TOPIC)

def on_message(client, userdata, msg):
    try:
        message = msg.payload.decode() 
        json_data = json.loads(message) 
        print(f"Received message: {json_data}") 
        update_text(message) 
        
        rotary = json_data.get('rotary', 0)
        temp = json_data.get('temp', 0) / 10
        humi = json_data.get('humi', 0) / 10
        
        rotary_label.config(text=f"가변저항: {rotary}")
        temp_label.config(text=f"온도: {temp}℃")
        humi_label.config(text=f"습도: {humi}%")
        
        insert_data(rotary, temp, humi)
    except Exception as e:
        print(f"Error processing message: {e}")

def insert_data(rotary, temp, humi):
    try:
        conn = pymysql.connect(
            host="localhost", 
            user="arduino", 
            password="123f5678", 
            database="python14"
        )
        cursor = conn.cursor()
        
        current_time = datetime.now()
        date = current_time.strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]  # 마이크로초 3자리까지
        
        sql = "INSERT INTO final_data (rotary, temp, humi, date) VALUES (%s, %s, %s, %s)"
        val = (rotary, temp, humi, date)
        
        cursor.execute(sql, val)
        conn.commit()
        
        cursor.close()
        conn.close()
        print("Data inserted successfully!")
    except pymysql.MySQLError as err:
        print(f"MySQL Error: {err}")
    except Exception as e:
        print(f"Unexpected error: {e}")

root = tk.Tk()
root.title("Arduino의 MQTT GUI")

label = ttk.Label(root, text="MQTT Messages")
label.pack(pady=10)

text_box = tk.Text(root, height=10, width=50)
text_box.pack(pady=10)

rotary_label = ttk.Label(root, text="가변저항: -", font=("Arial", 20))
rotary_label.pack(pady=5)
temp_label = ttk.Label(root, text="온도: -℃", font=("Arial", 20))
temp_label.pack(pady=5)
humi_label = ttk.Label(root, text="습도: -%", font=("Arial", 20))
humi_label.pack(pady=5)

button = ttk.Button(root, text="Publish Message", command=publish_message)
button.pack(pady=10)

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect(BROKER_ADDRESS, 1883, 60)
client.loop_start()

root.mainloop()
