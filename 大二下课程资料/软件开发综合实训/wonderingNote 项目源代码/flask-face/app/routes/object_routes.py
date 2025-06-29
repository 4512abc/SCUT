from flask import Blueprint, request, jsonify
from app.service.object_service import ObjectDetectionService
from app.utils.jwt_util import token_required
import logging
from PIL import Image as PILImage, UnidentifiedImageError

logger = logging.getLogger(__name__)

object_bp = Blueprint('object', __name__)
object_service = ObjectDetectionService()

@object_bp.route('/recognition', methods=['POST'])
@token_required
def detect_objects():
    """检测图片中的物体"""
    if 'image' not in request.files:
        return jsonify({'error': '未提供图片'}), 400

    image_file = request.files['image']
    try:
        # 尝试打开图片，检查是否为有效图像
        img = PILImage.open(image_file)
        img.verify()  # 验证图像数据
        image_file.seek(0)  # 重置文件指针
    except UnidentifiedImageError:
        return jsonify({'error': '无效的图片文件'}), 400
    except Exception as e:
        return jsonify({'error': f'图片处理失败: {str(e)}'}), 400

    result = object_service.detect(image_file)

    if result['success']:
        return jsonify({
            'code': 0,
            'message': result['message'],
            'found': result['found'],
            'detections': result['detections']
        })
    return jsonify({'error': result['message']}), 400
