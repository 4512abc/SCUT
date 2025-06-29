# 人脸检测工具
import face_recognition


def detect_faces(image_path):
    """
    检测图像中的人脸位置
    :param image_path: 图像文件路径
    :return: 人脸位置列表，每个位置是 (top, right, bottom, left)
    """
    # 加载图像
    image = face_recognition.load_image_file(image_path)

    # 检测人脸
    face_locations = face_recognition.face_locations(image)

    return face_locations