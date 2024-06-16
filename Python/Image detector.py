import cv2
import mediapipe as mp
import time
import os
import requests
from datetime import datetime

# Initialize MediaPipe Hands
mp_hands = mp.solutions.hands
hands = mp_hands.Hands()




# Initialize MediaPipe Drawing
mp_drawing = mp.solutions.drawing_utils

# Initialize video capture
cap = cv2.VideoCapture(0)

# Counter to track the number of images captured
capture_count = 0
def send_images_from_directory(directory_path, token, chat_id):
    url = f"https://api.telegram.org/bot{token}/sendPhoto"

    for filename in os.listdir(directory_path):
        if filename.endswith(".jpg") or filename.endswith(".jpeg") or filename.endswith(".png"):
            image_path = os.path.join(directory_path, filename)
            files = {'photo': open(image_path, 'rb')}
            data = {'chat_id': chat_id}
            response = requests.post(url, files=files, data=data)

            if response.status_code == 200:
                print(f"Image '{image_path}' sent successfully!")
            else:
                print(f"Failed to send image '{image_path}'. Status code: {response.status_code}")
                print(response.text)

token = "7040291127:AAEu9g8IjPQ5mBKUlx54ajW0uvsx66pqx1s"
chat_id = "-4198276598"
directory_path = "E:\Main Project\captured_images"

while cap.isOpened() and capture_count < 5:
    ret, frame = cap.read()
    if not ret:
        break

    # Flip the frame horizontally for a later selfie-view display
    frame = cv2.flip(frame, 1)

    # Convert the BGR image to RGB
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

    # Process the frame with MediaPipe Hands
    results = hands.process(rgb_frame)

    # Check if hands are detected
    if results.multi_hand_landmarks:
        for landmarks in results.multi_hand_landmarks:
            # Draw hand landmarks on the frame
            mp_drawing.draw_landmarks(frame, landmarks, mp_hands.HAND_CONNECTIONS)
            
            # Save the frame with a unique filename
            capture_count += 1
            current_time = datetime.now()
            time_string = current_time.strftime("%Y%m%d_%H%M%S")
            image_filename = f"image_{time_string}_{capture_count}.jpg"
            cv2.imwrite("captured_images/"+image_filename, frame)
    
    cv2.imshow('Hand Gesture Detection', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


send_images_from_directory(directory_path, token, chat_id)

# Release the video capture object and destroy all OpenCV windows
cap.release()
cv2.destroyAllWindows()
