# 使用官方 Python 镜像（推荐使用 Debian 基础版）
FROM python:3.10-bullseye

# 环境变量（强制禁用 GPU 和 GUI 依赖）
ENV DEBIAN_FRONTEND=noninteractive \
    PIP_NO_CACHE_DIR=1 \
    PYTHONUNBUFFERED=1 \
    DISPLAY=:0 \
    CUDA_VISIBLE_DEVICES="-1" \
    MEDIAPIPE_DISABLE_GPU="true"

# 设置工作目录
WORKDIR /app

# 安装 MediaPipe 系统依赖（关键修正）
RUN apt-get update && apt-get install -y --no-install-recommends \
    # OpenCV 和 MediaPipe 基础依赖
    libopencv-core4.5 \
    libopencv-highgui4.5 \
    libgl1 \
    libglib2.0-0 \
    libsm6 \
    libxext6 \
    libxrender1 \
    # 视频和图像处理
    ffmpeg \
    libavcodec-dev \
    libavformat-dev \
    libswscale-dev \
    # 开发工具（编译 dlib 等）
    build-essential \
    cmake \
    git \
    pkg-config \
    # 清理缓存
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# 安装 Python 依赖（分步安装避免冲突）
COPY requirements.txt .
RUN pip install --upgrade pip setuptools wheel
RUN pip install dlib --no-build-isolation
RUN pip install -r requirements.txt

# 复制项目代码
COPY . .

# 验证 MediaPipe 是否能导入（调试用）
RUN python -c "import mediapipe as mp; print(f'MediaPipe version: {mp.__version__}')"

# 暴露端口
EXPOSE 5000

# 启动命令（使用 gunicorn）
CMD ["gunicorn", "--bind", "0.0.0.0:5000", "run:app", "--workers=2", "--threads=4", "--timeout=120"]