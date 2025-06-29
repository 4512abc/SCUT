import mediapipe as mp
import cv2
import numpy as np

class SemanticRecognizer:
    def __init__(self, model_path):
        BaseOptions = mp.tasks.BaseOptions
        GestureRecognizer = mp.tasks.vision.GestureRecognizer
        GestureRecognizerOptions = mp.tasks.vision.GestureRecognizerOptions
        VisionRunningMode = mp.tasks.vision.RunningMode

        options = GestureRecognizerOptions(
            base_options=BaseOptions(model_asset_path=model_path),
            running_mode=VisionRunningMode.IMAGE,
            num_hands=2,
            min_hand_detection_confidence=0.5
        )
        self.recognizer = GestureRecognizer.create_from_options(options)

    def process_frame(self, frame):
        frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        mp_image = mp.Image(image_format=mp.ImageFormat.SRGB, data=frame_rgb)
        recognition_result = self.recognizer.recognize(mp_image)

        gestures = []
        if recognition_result.gestures:
            for handedness, gestures_list in zip(recognition_result.handedness, recognition_result.gestures):
                gestures.append({
                    'hand': handedness[0].category_name,
                    'gesture': gestures_list[0].category_name,
                    'confidence': gestures_list[0].score
                })

        return gestures
