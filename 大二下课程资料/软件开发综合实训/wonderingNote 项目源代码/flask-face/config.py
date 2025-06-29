class Config:
    # MySQL配置
    MYSQL_HOST = 'xxx.xxx.xxx.xxx' # 修改为你运行MySQL服务器的地址
    MYSQL_PORT = 3306 # 修改为你运行MySQL的端口，一般就是3306
    MYSQL_USER = 'xxx'  # 修改为你的MySQL用户名
    MYSQL_PASSWORD = 'xxx'  # 修改为你的MySQL密码
    MYSQL_DATABASE = 'xxx' # 修改为你要连接的数据库名

    # SQLAlchemy配置
    SQLALCHEMY_DATABASE_URI = f'mysql+pymysql://{MYSQL_USER}:{MYSQL_PASSWORD}@{MYSQL_HOST}:{MYSQL_PORT}/{MYSQL_DATABASE}'
    SQLALCHEMY_TRACK_MODIFICATIONS = False
    SQLALCHEMY_POOL_SIZE = 10
    SQLALCHEMY_MAX_OVERFLOW = 20

    # 其他配置...
    JWT_SECRET = 'maohe101'
    JWT_EXPIRE_TIME = 36000000  # 10小时
    JWT_TOKEN_PREFIX = 'Bearer'
    JWT_HEADER = 'Authorization'