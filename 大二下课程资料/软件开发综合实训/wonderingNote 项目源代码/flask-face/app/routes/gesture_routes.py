from flask import Blueprint, request, jsonify
from app.service.gesture_service import GestureService
from app.utils.jwt_util import token_required
import logging

logger = logging.getLogger(__name__)

gesture_bp = Blueprint('gesture', __name__)
gesture_service = GestureService()

@gesture_bp.route('/number', methods=['POST'])
@token_required
def detect_number():
    """检测倒计时数字手势（6-1）"""
    if 'image' not in request.files:
        logger.warning("请求中未包含 image 文件")
        return jsonify({'error': '未提供图片'}), 400

    image_file = request.files['image']
    logger.debug(f"接收到倒计时图像: filename={image_file.filename}, content_type={image_file.content_type}")
    result = gesture_service.detect_countdown(image_file)

    if result['success']:
        return jsonify({
            'code': 0,
            'message': result['message'],
            'found': result['found'],
            'detections': result['detections']
        })

    logger.error(f"倒计时检测失败: {result['message']}")
    return jsonify({'error': result['message']}), 400


@gesture_bp.route('/semantic', methods=['POST'])
@token_required
def detect_semantic():
    """检测语义手势（OK、Victory等）"""
    logger.debug("接收到语义手势检测请求")

    if 'image' not in request.files:
        logger.warning("请求中未包含 image 文件")
        return jsonify({'error': '未提供图片'}), 400

    image_file = request.files['image']
    logger.debug(f"接收到语义图像: filename={image_file.filename}, content_type={image_file.content_type}")

    result = gesture_service.detect_semantic(image_file)

    if result['success']:
        logger.debug(f"检测成功: found={result['found']}, detections={result['detections']}")
        return jsonify({
            'code': 0,
            'message': result['message'],
            'found': result['found'],
            'detections': result['detections']
        })

    logger.error(f"语义检测失败: {result['message']}")
    return jsonify({'error': result['message']}), 400
