import os

import paddle
import paddle.vision.models as models
from paddle.vision.transforms import Compose, Resize, Normalize, ToTensor
from PIL import Image
import json
import urllib.request
import numpy as np
import io
import logging

logger = logging.getLogger(__name__)

class ObjectDetectionService:
    def __init__(self):
        self.model = models.resnet50(pretrained=True)
        self.model.eval()

        self.transform = Compose([
            Resize((224, 224)),
            ToTensor(),
            Normalize(mean=[0.485, 0.456, 0.406],
                      std=[0.229, 0.224, 0.225])
        ])

        # 加载ImageNet标签
        url = "https://storage.googleapis.com/download.tensorflow.org/data/imagenet_class_index.json"
        with urllib.request.urlopen(url) as urlfile:
            self.class_idx = json.load(urlfile)

        # 获取当前文件的目录
        current_dir = os.path.dirname(os.path.abspath(__file__))
        # 构建文件的绝对路径
        file_path = os.path.join(current_dir, 'chinese_labels.json')

        with open(file_path, 'r', encoding='utf-8') as f:
            self.chinese_labels = json.load(f)

    def detect(self, image_file):
        try:
            img = Image.open(io.BytesIO(image_file.read())).convert('RGB')
            img = self.transform(img)
            img = img.unsqueeze(0)

            output = self.model(img)
            pred = paddle.argmax(output, axis=1)
            pred_idx = int(pred.numpy().item())
            pred_label = self.class_idx[str(pred_idx)][1]
            pred_nxxx = self.class_idx[str(pred_idx)][0]
            chinese_label = self.chinese_labels.get(str(pred_nxxx), "未知")

            return {
                'success': True,
                'message': '检测成功',
                'found': True,
                'detections': {
                    'class_name': pred_label,
                    'class_id': pred_idx,
                    'chinese_class_name': chinese_label
                }
            }

        except Exception as e:
            logger.error(f"物体检测异常: {e}")
            return {'success': False, 'message': str(e)}
