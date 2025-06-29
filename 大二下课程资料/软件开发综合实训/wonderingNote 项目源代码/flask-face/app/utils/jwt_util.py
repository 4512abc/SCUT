import jwt
from datetime import datetime, timedelta
from functools import wraps
from flask import request, jsonify, current_app
import logging

logger = logging.getLogger(__name__)

class JWTUtils:
    @staticmethod
    def get_token(claims):
        """
        生成token
        :param claims: 存放的用户信息字典
        :return: token字符串
        """
        try:
            if not claims:
                raise ValueError("Claims不能为空")

            # 添加过期时间
            expire = datetime.utcnow() + timedelta(milliseconds=current_app.config['JWT_EXPIRE_TIME'])
            claims['exp'] = expire

            # 生成token
            token = jwt.encode(
                claims,
                current_app.config['JWT_SECRET'],
                algorithm='HS512'
            )
            return current_app.config['JWT_TOKEN_PREFIX'] + " " + token

        except Exception as e:
            logger.error(f"生成token失败: {str(e)}")
            raise RuntimeError("生成token失败")

    @staticmethod
    def parse_token(token):
        """解析Token"""
        if not token:
            logger.error("Token为空")
            raise ValueError("Token不能为空")

        try:
            logger.info(f"开始解析token: {token[:20]}...")
            # 移除Bearer前缀，注意要移除Bearer和空格
            actual_token = token.replace(current_app.config['JWT_TOKEN_PREFIX'] + " ", "").strip()
            logger.info(f"移除前缀后的token: {actual_token[:20]}...")

            # 直接使用jwt.decode，指定算法为HS512
            payload = jwt.decode(
                actual_token,
                current_app.config['JWT_SECRET'],
                algorithms=['HS512']
            )
            logger.info(f"解析得到的payload: {payload}")
            return payload

        except jwt.ExpiredSignatureError:
            logger.error("Token已过期")
            raise RuntimeError("Token已过期")
        except jwt.InvalidTokenError as e:
            logger.error(f"Token解析失败: {str(e)}")
            raise RuntimeError("Token解析失败")

    @staticmethod
    def validate_token(token):
        """
        验证token是否有效
        :param token: JWT token字符串
        :return: 验证通过返回True，否则返回False
        """
        try:
            JWTUtils.parse_token(token)
            return True
        except:
            return False

    @staticmethod
    def get_claims(token):
        """获取Claims"""
        try:
            claims = JWTUtils.parse_token(token)
            logger.info(f"获取到的claims: {claims}")
            # 处理特殊类型（如Long）
            processed_claims = {}
            for key, value in claims.items():
                if isinstance(value, (int, str)):
                    processed_claims[key] = value
                elif value is None:
                    processed_claims[key] = ""
            return processed_claims
        except Exception as e:
            logger.error(f"获取Claims失败: {str(e)}")
            raise RuntimeError("获取Claims失败")

    @staticmethod
    def is_need_update(token):
        """
        检查token是否需要更新
        :param token: JWT token字符串
        :return: 如果需要更新返回True，否则返回False
        """
        try:
            payload = JWTUtils.parse_token(token)
            exp_timestamp = payload['exp']
            now = datetime.utcnow().timestamp()
            # 如果剩余过期时间少于过期时长的一半时需要更新
            return (exp_timestamp - now) * 1000 < (current_app.config['JWT_EXPIRE_TIME'] >> 1)
        except:
            return True


def token_required(f):
    @wraps(f)
    def decorated(*args, **kwargs):
        logger.info("\n=== Token验证开始 ===")

        # 1. 获取token
        token = request.headers.get(current_app.config['JWT_HEADER'])
        logger.info(f"请求头中的token: {token}")
        logger.info(f"当前配置的header: {current_app.config['JWT_HEADER']}")
        logger.info(f"当前配置的prefix: {current_app.config['JWT_TOKEN_PREFIX']}")
        logger.info(f"当前配置的secret: {current_app.config['JWT_SECRET'][:5]}...")

        if not token:
            logger.error("未提供令牌")
            return jsonify({'error': '未提供令牌'}), 401

        try:
            # 2. 获取claims
            claims = JWTUtils.get_claims(token)
            logger.info(f"完整的claims内容: {claims}")

            # 3. 尝试获取所有可能的ID字段
            user_id = claims.get('userId')  # Spring Boot常用
            if user_id is None:
                user_id = claims.get('user_id')  # 下划线形式
            if user_id is None:
                user_id = claims.get('id')  # 简单形式
            if user_id is None:
                user_id = claims.get('sub')  # JWT标准字段

            logger.info(f"最终获取到的user_id: {user_id}")

            # 4. 调试其他关键字段
            logger.info("Claims中的所有字段:")
            for key, value in claims.items():
                logger.info(f"  {key}: {value}")

            if user_id is None:
                logger.error("未能从token中提取到user_id")
                return jsonify({'error': '无法获取用户ID'}), 401

            request.user_id = user_id
            logger.info(f"成功设置request.user_id: {request.user_id}")
            logger.info("=== Token验证完成 ===\n")

            return f(*args, **kwargs)

        except Exception as e:
            logger.error(f"Token验证失败: {str(e)}", exc_info=True)
            return jsonify({'error': str(e)}), 401

    return decorated