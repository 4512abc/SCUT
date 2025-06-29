import os

import torch
import numpy as np
import cv2
from facenet_pytorch import MTCNN, InceptionResnetV1
from app.models.face_model import db, FaceEmbedding
from datetime import datetime


class FaceService:
    def __init__(self):
        self.device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')
        self.mtcnn = MTCNN(
            image_size=160,
            min_face_size=20,
            thresholds=[0.6, 0.7, 0.7],  # 提高检测阈值
            keep_all=False,  # 只保留最大的人脸
            device=self.device
        )
        # 构造模型文件绝对路径（根据你的项目结构调整）
        current_dir = os.path.dirname(os.path.abspath(__file__))
        model_path = os.path.abspath(os.path.join(current_dir, '..', 'models', 'vggface2.pt'))

        # 载入权重并过滤掉logits层参数
        state_dict = torch.load(model_path, map_location=self.device)
        filtered_state_dict = {k: v for k, v in state_dict.items() if not k.startswith('logits.')}

        # 初始化模型，classify=False表示只做特征提取
        self.resnet = InceptionResnetV1(classify=False)
        self.resnet.load_state_dict(filtered_state_dict)
        self.resnet.eval().to(self.device)

        self.threshold = 0.8

    def process_image(self, image_file):
        """处理上传的图片文件，提取人脸特征向量"""
        image_bytes = image_file.read()
        nparr = np.frombuffer(image_bytes, np.uint8)
        img = cv2.imdecode(nparr, cv2.IMREAD_COLOR)

        if img is None:
            raise ValueError("无法读取图片")

        # BGR转RGB
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

        # 检测和对齐人脸
        face = self.mtcnn(img)  # keep_all=False时返回单个人脸tensor
        if face is None:
            raise ValueError("未检测到人脸")

        # 不需要检查多个人脸，因为keep_all=False时只返回置信度最高的一个人脸
        # 直接将face转换为batch形式
        aligned = face.unsqueeze(0).to(self.device)

        # 提取特征向量
        with torch.no_grad():
            embedding = self.resnet(aligned).cpu().numpy()

        return embedding[0]

    def register_face(self, user_id, image_file):
        """注册用户人脸"""
        try:
            # 提取特征向量
            embedding = self.process_image(image_file)

            # 保存到数据库
            face_embedding = FaceEmbedding.query.filter_by(user_id=user_id).first()
            if face_embedding is None:
                face_embedding = FaceEmbedding(user_id=user_id)

            face_embedding.set_embedding(embedding)
            db.session.add(face_embedding)
            db.session.commit()

            return True, "人脸注册成功"
        except Exception as e:
            db.session.rollback()
            return False, str(e)

    def verify_face(self, user_id, image_file):
        """验证用户人脸"""
        try:
            # 加载存储的特征向量
            face_embedding = FaceEmbedding.query.filter_by(user_id=user_id).first()
            if face_embedding is None:
                return False, "用户未注册人脸", None

            stored_embedding = face_embedding.get_embedding()

            # 提取当前图片的特征向量
            new_embedding = self.process_image(image_file)

            # 计算相似度
            distance = np.linalg.norm(new_embedding - stored_embedding)
            confidence = 1 - (distance / 2)
            is_match = distance < self.threshold

            result = {
                'match': bool(is_match),
                'confidence': float(confidence),
                'user_id': user_id,
                'message': '验证成功' if is_match else '验证失败',
                'code': '0' if is_match else '-1',
            }

            return True, None, result
        except Exception as e:
            result = {
                'match': False,
                'code': '-1',
                'message': str(e),
            }
            return False, str(e), result

    def check_registered(self, user_id):
        """检查用户是否已经注册了人脸特征向量"""
        face_embedding = FaceEmbedding.query.filter_by(user_id=user_id).first()
        if face_embedding is None:
            return False, "用户未注册人脸"
        return True, "用户已注册人脸"