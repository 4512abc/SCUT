import io
from app.models.scene_recognizer import SceneRecognizer
from PIL import Image
import logging

logger = logging.getLogger(__name__)

class SceneRecognitionService:
    def __init__(self):
        self.recognizer = SceneRecognizer()

    def recognize(self, image_file):
        try:
            image = Image.open(io.BytesIO(image_file.read())).convert('RGB')
            pred_label, confidence = self.recognizer.predict(image)

            return {
                'success': True,
                'message': '识别成功',
                'found': confidence > 0.6,  # 可以根据需求调整阈值
                'detections': {
                    'scene': pred_label,
                    'confidence': confidence
                }
            }
        except Exception as e:
            logger.error(f"场景识别异常: {e}")
            return {'success': False, 'message': str(e)}
