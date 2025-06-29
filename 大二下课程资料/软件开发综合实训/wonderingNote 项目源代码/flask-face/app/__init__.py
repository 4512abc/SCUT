from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from config import Config
from app.models.face_model import db

def create_app():
    app = Flask(__name__)
    # 加载配置
    app.config.from_object(Config)

    # 初始化SQLAlchemy，这只是建立连接，不会创建表
    db.init_app(app)

    # 注册蓝图
    from app.routes.face_routes import face_bp
    app.register_blueprint(face_bp, url_prefix='/api/face')

    from app.routes.object_routes import object_bp
    app.register_blueprint(object_bp, url_prefix='/api/object')

    from app.routes.gesture_routes import gesture_bp
    app.register_blueprint(gesture_bp, url_prefix='/api/gesture')

    from app.routes.scene_routes import scene_bp
    app.register_blueprint(scene_bp, url_prefix='/api/scene')

    return app