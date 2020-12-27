import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
import cv2

f = open('output.txt','w')

def output_label(Y):
  temp = []
  if Y == 1:
    temp = 'a'
  if Y == 2:
    temp = 'b'
  if Y == 3:
    temp = 'c'
  if Y == 4:
    temp = 'd'
  if Y == 5:
    temp = 'e'
  if Y == 6:
    temp = 'f'
  if Y == 7:
    temp = 'g'
  if Y == 8:
    temp = 'h'
  if Y == 9:
    temp = 'i'
  if Y == 10:
    temp = 'j'
  if Y == 11:
    temp = 'k'
  if Y == 12:
    temp = 'l'
  if Y == 13:
    temp = 'm'
  if Y == 14:
    temp = 'n'
  if Y == 15:
    temp = 'o'
  if Y == 16:
    temp = 'p'
  if Y == 17:
    temp = 'q'
  if Y == 18:
    temp = 'r'
  if Y == 19:
    temp = 's'
  if Y == 20:
    temp = 't'
  if Y == 21:
    temp = 'u'
  if Y == 22:
    temp = 'v'
  if Y == 23:
    temp = 'w'
  if Y == 24:
    temp = 'x'
  if Y == 25:
    temp = 'y'
  if Y == 26:
    temp = 'z'
  return temp

class CNN_Layer2(nn.Module):
  
  def __init__(self):
    super(CNN_Layer2, self).__init__()

    self.conv1 = nn.Conv2d(1, 16, 3)
    self.pool1 = nn.MaxPool2d(2,2)

    self.conv2 = nn.Conv2d(16, 32 ,3)
    self.pool2 = nn.MaxPool2d(2,2)

    self.fc1 = nn.Linear(800, 256)
    self.fc2 = nn.Linear(256, 27)

  def forward(self, x):
    x = self.pool1(F.relu(self.conv1(x)))
    x = self.pool2(F.relu(self.conv2(x)))
    x = x.view(-1, self.num_flat_features(x))
    x = F.relu(self.fc1(x))
    x = self.fc2(x)
    return x

  def num_flat_features(self,x):
    size = x.size()[1:]
    num_features = 1
    for s in size:
      num_features *= s
    return num_features

model = CNN_Layer2()

PATH = 'C:/Study2019/Win32/changetocpp/Project3/9202.pth' # train된 net file 경로
model.load_state_dict(torch.load(PATH,map_location='cpu'))

input = np.zeros((1,1,28,28))

image = cv2.imread("C:/Study2019/Win32/changetocpp/Project3/screen.jpg") # input image 경로
image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
input[0,0,:,:] = cv2.resize(image, dsize=(28, 28), interpolation=cv2.INTER_AREA)
input = (input - 255)*(-1)
input[input==-0]=0

test_loader = torch.from_numpy(input)
test_predict = model(test_loader.float())

test_predict_ar = np.zeros((1,))
test_predict = test_predict.to('cpu')
test_predict_np = test_predict.detach().numpy()
test_predict_ar = np.argmax(test_predict_np[:])
output = output_label(test_predict_ar)

f.write(output)
f.close()
