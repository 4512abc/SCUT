from flask import Blueprint, request, jsonify
from app.service.scene_service import SceneRecognitionService
from app.utils.jwt_util import token_required
import logging

logger = logging.getLogger(__name__)

scene_bp = Blueprint('scene', __name__)
scene_service = SceneRecognitionService()

@scene_bp.route('/recognition', methods=['POST'])
@token_required
def recognize_scene():
    """识别图片场景"""
    if 'image' not in request.files:
        return jsonify({'error': '未提供图片'}), 400

    image_file = request.files['image']
    result = scene_service.recognize(image_file)

    if result['success']:
        return jsonify({
            'code': 0,
            'message': result['message'],
            'found': result['found'],
            'detections': result['detections']
        })
    return jsonify({'error': result['message']}), 400
