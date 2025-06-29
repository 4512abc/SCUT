import torch
import cv2
from torchvision import transforms
from app.models.gesture_number_net import NumberGestureNet
from torchvision import models

class NumberRecognizer:
    def __init__(self, model_path):
        self.device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
        self.model = self._load_model(model_path)

        # 图像预处理
        self.transform = transforms.Compose([
            transforms.ToPILImage(),
            transforms.Resize((224, 224)),
            transforms.ToTensor(),
            transforms.Normalize(mean=[0.485, 0.456, 0.406],
                                 std=[0.229, 0.224, 0.225])
        ])

    def _load_model(self, model_path):
        base_model = models.resnet34(weights=None)
        modules = list(base_model.children())[:-2]
        model = NumberGestureNet(modules, num_classes=11)  # 11类（0 - 10）

        # 加载权重
        checkpoint = torch.load(model_path, map_location=self.device)
        model.load_state_dict(checkpoint['model_state_dict'])
        model.to(self.device).eval()
        self.classes = checkpoint['classes']
        return model

    def predict(self, frame):
        image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        tensor = self.transform(image).unsqueeze(0).to(self.device)

        with torch.no_grad():
            output = self.model(tensor)
            prob = torch.softmax(output, dim=1)
            confidence, predicted = torch.max(prob, 1)

        return self.classes[predicted.item()], confidence.item()
