import os
import torch
import torch.nn as nn
from fastai.vision.all import *
from PIL import Image as PILImage
from pathlib import Path

class SceneRecognizer:
    def __init__(self):
        # 设置路径
        base_dir = Path(__file__).parent
        self.models_dir = base_dir / "trained_models"  # 模型保存路径
        self.data_dir = base_dir / "dataset/seg_train"  # 训练数据路径

        # 准备数据（与训练时相同的方式）
        self.dls = DataBlock(
            blocks=(ImageBlock, CategoryBlock),
            get_items=get_image_files,
            splitter=RandomSplitter(valid_pct=0.2, seed=42),
            get_y=parent_label,
            item_tfms=Resize(460),
            batch_tfms=[*aug_transforms(size=224), Normalize.from_stats(*imagenet_stats)]
        ).dataloaders(self.data_dir, bs=64)

        # 初始化模型
        self.learn = vision_learner(
            self.dls,
            CustomResNet50,  # 使用自定义模型
            metrics=[accuracy],
            path=self.models_dir
        )

        # 加载权重
        checkpoint_path = self.models_dir / 'scene_selfTrain.pth'
        checkpoint = torch.load(checkpoint_path, map_location=torch.device('cpu'))
        self.learn.model.load_state_dict(checkpoint['model_state_dict'])
        self.learn.dls.vocab = checkpoint['classes']  # 恢复类别

    def predict(self, pil_image):
        # 对图片进行预处理（与训练时相同的转换）
        dl = self.learn.dls.test_dl([pil_image])  # 包装成 DataLoader 格式

        # 获取第一个批次的图片
        batch = dl.one_batch()
        inputs = batch[0]  # 获取图片数据

        # 确保张量在 CPU 上
        inputs = inputs.cpu()

        # 进行预测
        pred, pred_idx, probs = self.learn.predict(inputs[0])  # 使用第一个图片进行预测

        # 返回预测结果
        return pred, float(probs[pred_idx])


# 自定义带 Dropout 的 ResNet50
class CustomResNet50(nn.Module):
    def __init__(self, pretrained=True):
        super().__init__()
        # 创建 ResNet50 模型实例
        resnet_model = resnet50(pretrained=pretrained)
        # 使用 create_body 提取主体部分
        self.body = create_body(resnet_model, pretrained=pretrained)
        # 获取 ResNet50 的最后一层特征数
        nf = num_features_model(nn.Sequential(*self.body.children()))
        # 自定义的全连接层
        self.head = nn.Sequential(
            nn.AdaptiveAvgPool2d(1),  # 全局平均池化
            nn.Flatten(),  # 展平
            nn.Dropout(0.5),  # 添加 Dropout
            nn.Linear(nf, 6)  # 默认 6 分类，根据模型实际训练来的类别数
        )

    def forward(self, x):
        x = self.body(x)  # 通过 ResNet50 的主体部分
        x = self.head(x)  # 通过自定义的全连接层
        return x
