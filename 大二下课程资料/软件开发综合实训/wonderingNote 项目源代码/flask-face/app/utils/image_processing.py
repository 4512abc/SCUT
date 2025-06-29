# 图像处理工具

from PIL import Image
import cv2


def process_image(image_path, output_path=None, resize_width=None):
    """
    处理图像（如调整大小）
    :param image_path: 输入图像路径
    :param output_path: 输出图像路径（可选）
    :param resize_width: 调整后的宽度（可选）
    :return: 处理后的图像路径
    """
    # 使用 OpenCV 加载图像
    image = cv2.imread(image_path)

    # 如果需要调整大小
    if resize_width:
        height, width = image.shape[:2]
        aspect_ratio = height / width
        new_height = int(resize_width * aspect_ratio)
        image = cv2.resize(image, (resize_width, new_height))

    # 如果指定了输出路径，保存图像
    if output_path:
        cv2.imwrite(output_path, image)
        return output_path

    return image_path


def crop_face(image_path, face_location, output_path=None):
    """
    裁剪人脸区域
    :param image_path: 输入图像路径
    :param face_location: 人脸位置 (top, right, bottom, left)
    :param output_path: 输出图像路径（可选）
    :return: 裁剪后的人脸图像路径
    """
    # 使用 Pillow 加载图像
    image = Image.open(image_path)

    # 裁剪人脸区域
    top, right, bottom, left = face_location
    cropped_image = image.crop((left, top, right, bottom))

    # 如果指定了输出路径，保存裁剪后的图像
    if output_path:
        cropped_image.save(output_path)
        return output_path

    return cropped_image