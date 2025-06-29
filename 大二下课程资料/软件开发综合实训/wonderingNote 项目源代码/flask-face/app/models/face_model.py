from datetime import datetime
from flask_sqlalchemy import SQLAlchemy
import numpy as np
import pickle

db = SQLAlchemy()

class FaceEmbedding(db.Model):
    """人脸特征向量模型"""
    __tablename__ = 'face_features'

    id = db.Column(db.BigInteger, primary_key=True, autoincrement=True)
    user_id = db.Column('user_id', db.BigInteger, unique=True, nullable=False)
    face_vector = db.Column('face_vector', db.Text, nullable=True)
    create_time = db.Column('create_time', db.DateTime, default=datetime.utcnow)

    def set_embedding(self, embedding_array):
        """将numpy数组序列化后存储为base64字符串"""
        import base64
        embedding_bytes = pickle.dumps(embedding_array)
        self.face_vector = base64.b64encode(embedding_bytes).decode('utf-8')

    def get_embedding(self):
        """从base64字符串获取特征向量"""
        import base64
        if self.face_vector:
            embedding_bytes = base64.b64decode(self.face_vector.encode('utf-8'))
            return pickle.loads(embedding_bytes)
        return None