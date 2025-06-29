import cv2
import dlib
import matplotlib.pyplot as plt
import numpy as np


def test_face_detection():
    # 读取图片
    img_path = './data/f170_1.png'
    img = cv2.imread(img_path)
    origin_img = img.copy()

    # 定义人脸检测器
    detector = dlib.get_frontal_face_detector()

    # 定义人脸关键点检测器
    predictor = dlib.shape_predictor("./shape_predictor_68_face_landmarks.dat")

    # 检测人脸
    faces = detector(img, 0)

    # 如果存在人脸
    print(f"Found {len(faces)} faces in this image.")

    if len(faces):
        for face in faces:
            landmarks = np.matrix([[p.x, p.y] for p in predictor(img, face).parts()])
            for point in landmarks:
                pos = (point[0, 0], point[0, 1])
                cv2.circle(img, pos, 1, color=(0, 255, 255), thickness=3)
    else:
        print("Face not found!")

    # 显示结果
    cv2.namedWindow("Origin Face", cv2.WINDOW_FREERATIO)
    cv2.namedWindow("Detected Face", cv2.WINDOW_FREERATIO)
    cv2.imshow("Origin Face", origin_img)
    cv2.waitKey(0)
    cv2.imshow("Detected Face", img)
    cv2.waitKey(0)


if __name__ == '__main__':
    test_face_detection()