from flask import Blueprint, request, jsonify
from app.service.face_service import FaceService
from app.utils.jwt_util import token_required
import logging

logger = logging.getLogger(__name__)

face_bp = Blueprint('face', __name__)
face_service = FaceService()

@face_bp.route('/register', methods=['POST'])
@token_required

def register_face():
    """注册用户人脸"""
    logger.info("\n=== 开始处理人脸注册请求 ===")

    if 'image' not in request.files:
        logger.error("请求中未包含图片文件")
        return jsonify({'error': '未提供图片'}), 400

    image_file = request.files['image']
    user_id = request.user_id
    logger.info(f"从request对象获取到的user_id: {user_id}")

    if user_id is None:
        logger.error("user_id为空，token验证可能出现问题")
        return jsonify({'error': 'user_id为空'}), 400

    success, message = face_service.register_face(user_id, image_file)
    logger.info(f"注册结果: success={success}, message={message}")
    logger.info("=== 人脸注册请求处理完成 ===\n")

    if success:
        return jsonify({
            'code': 0,
            'message': message,
            'user_id': user_id
        })
    return jsonify({'error': message}), 400

@face_bp.route('/verify', methods=['POST'])
@token_required
def verify_face():
    """验证用户人脸"""
    if 'image' not in request.files:
        return jsonify({'error': '未提供图片'}), 400

    image_file = request.files['image']
    user_id = request.user_id  # 从token中获取user_id

    success, error, result = face_service.verify_face(user_id, image_file)
    if success:
        return jsonify(result)
    return jsonify({'error': error}), 404 if error == "用户未注册人脸" else 400

@face_bp.route('/check_registered', methods=['POST'])
@token_required
def check_registered():
    """检查用户是否已经注册了人脸特征向量"""
    user_id = request.user_id  # 从token中获取user_id

    if user_id is None:
        logger.error("user_id为空，token验证可能出现问题")
        return jsonify({'error': 'user_id为空'}), 200

    success, message = face_service.check_registered(user_id)
    if success:
        return jsonify({
            'code': 0,
            'message': message,
            'user_id': user_id
        })
    return jsonify({'error': message, 'code': "-1"}), 200