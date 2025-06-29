# app/service/hand_gesture_net.py
import torch.nn as nn

class NumberGestureNet(nn.Module):
    def __init__(self, backbone_modules, num_classes):
        super().__init__()
        self.backbone = nn.Sequential(*backbone_modules)

        self.attention = nn.Sequential(
            nn.Conv2d(512, 64, 1),
            nn.BatchNorm2d(64),
            nn.ReLU(),
            nn.Conv2d(64, 1, 1),
            nn.Sigmoid()
        )

        self.classifier = nn.Sequential(
            nn.AdaptiveAvgPool2d(1),
            nn.Flatten(),
            nn.Linear(512, 256),
            nn.BatchNorm1d(256),
            nn.ReLU(),
            nn.Dropout(0.4),
            nn.Linear(256, num_classes)
        )

    def forward(self, x):
        features = self.backbone(x)
        attention = self.attention(features)
        attended_features = features * attention
        out = self.classifier(attended_features)
        return out
