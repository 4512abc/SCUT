import os
import logging
import cv2
import numpy as np
from concurrent.futures import ThreadPoolExecutor, TimeoutError

from app.models.gesture_number_recognizer import NumberRecognizer
from app.models.gesture_semantic_recognizer import SemanticRecognizer

logger = logging.getLogger(__name__)

class GestureService:
    def __init__(self):
        current_dir = os.path.dirname(os.path.abspath(__file__))
        number_model_path = os.path.join(current_dir, '../models/trained_models/gesture_number.pth')
        semantic_model_path = os.path.join(current_dir, '../models/trained_models/gesture_semantic_mediapipe.task')

        if not os.path.exists(number_model_path):
            raise FileNotFoundError(f"模型文件未找到: {number_model_path}")
        if not os.path.exists(semantic_model_path):
            raise FileNotFoundError(f"模型文件未找到: {semantic_model_path}")

        self.countdown_model = NumberRecognizer(model_path=number_model_path)
        self.semantic_model = SemanticRecognizer(model_path=semantic_model_path)

    def detect_countdown(self, image_file):
        try:
            logger.debug("开始处理倒计时手势图像")
            file_bytes = np.frombuffer(image_file.read(), np.uint8)
            logger.debug(f"读取图像字节数: {len(file_bytes)}")

            frame = cv2.imdecode(file_bytes, cv2.IMREAD_COLOR)
            if frame is None:
                logger.warning("图像解码失败")
                return {'success': False, 'message': '无效的图片格式'}

            gesture, confidence = self.countdown_model.predict(frame)
            found = confidence > 0.7

            logger.debug(f"检测结果: gesture={gesture}, confidence={confidence:.3f}, found={found}")

            return {
                'success': True,
                'message': '检测成功',
                'found': found,
                'detections': {
                    'gesture': gesture,
                    'confidence': confidence
                }
            }
        except Exception as e:
            logger.error(f"倒计时手势检测异常: {e}", exc_info=True)
            return {'success': False, 'message': f'处理错误: {str(e)}'}

    def detect_semantic(self, image_file):
        try:
            logger.debug("开始处理语义手势图像")

            file_pos = image_file.tell()
            file_bytes = np.frombuffer(image_file.read(), np.uint8)
            image_file.seek(file_pos)

            logger.debug(f"读取图像字节数: {len(file_bytes)}")
            frame = cv2.imdecode(file_bytes, cv2.IMREAD_COLOR)
            if frame is None:
                logger.warning("图像解码失败")
                return {'success': False, 'message': '无效的图片格式'}

            logger.debug(f"图像解码成功: shape={frame.shape}")

            with ThreadPoolExecutor(max_workers=1) as executor:
                logger.debug("提交语义手势模型处理任务")
                future = executor.submit(self.semantic_model.process_frame, frame)
                try:
                    gestures = future.result(timeout=10)
                    logger.debug(f"模型检测完成: {gestures}")
                except TimeoutError:
                    logger.warning("语义手势检测超时")
                    return {'success': False, 'message': '处理超时'}

            return {
                'success': True,
                'message': '检测成功',
                'found': bool(gestures),
                'detections': gestures
            }

        except Exception as e:
            logger.error(f"语义手势检测异常: {str(e)}", exc_info=True)
            return {'success': False, 'message': f'处理错误: {str(e)}'}
