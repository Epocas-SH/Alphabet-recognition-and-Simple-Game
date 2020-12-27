import numpy as np
import matplotlib.pyplot as plt
import pickle
import torch
import torchvision
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torchvision import datasets, transforms

# Download MNIST dataset 
train_dataset = torchvision.datasets.EMNIST(root='./data/EMNIST', 
                                            split='letters',
                                           train=True, 
                                           download=True)
test_dataset = torchvision.datasets.EMNIST(root='./data/EMNIST', 
                                           split='letters',
                                          train=False, 
                                          download=True)
# Transforming input data
traindata = train_dataset.train_data.numpy()
testdata = test_dataset.test_data.numpy()
trainlabel = train_dataset.train_labels.numpy()
testlabel = test_dataset.test_labels.numpy()

traindata_1 = np.transpose(traindata,(0,2,1))
testdata_1 = np.transpose(testdata,(0,2,1))

traindata_1 = traindata_1.reshape(len(traindata_1),1,28,28)
testdata_1 = testdata_1.reshape(len(testdata_1),1,28,28)

class SH_train_dataset(torch.utils.data.Dataset):
  
  def __init__(self, data, target, transforms = None):
    self.len = np.shape(target)[0]
    self.data = torch.FloatTensor(data) # data = data to be trained
    self.target = torch.LongTensor(target) # target = true label

  def __len__(self):
    return self.len

  def __getitem__(self, index):
    return self.data[index], self.target[index], index

class SH_valid_dataset(torch.utils.data.Dataset):

  def __init__(self, data, target, transforms = None):
    self.len = np.shape(data)[0]
    self.data = torch.FloatTensor(data)
    self.target = torch.LongTensor(target)

  def __len__(self):
    return self.len
  
  def __getitem__(self, index):
    return self.data[index], self.target[index], index

BatchSize = 5000

traindataset = SH_train_dataset(traindata_1,trainlabel)
testdataset = SH_valid_dataset(testdata_1,testlabel)

train_loader = torch.utils.data.DataLoader(traindataset, batch_size=BatchSize)
valid_loader = torch.utils.data.DataLoader(testdataset, batch_size=BatchSize)

# Define Convolutional Neural Network (2 layer)
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
criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.parameters(), lr = 0.0006)

loss_train = []
loss_valid = []

for epoch in range(50):

# Training the net
  model.train()
  print('Train Epoch {}'.format(epoch+1))

  for batch_idx, (data, target, index) in enumerate(train_loader):
    optimizer.zero_grad()
    output = model(data)
    loss = criterion(output, target)
    loss.backward()
    optimizer.step()

    if (1+batch_idx) % 5 == 0: # print the status
      print('{}/{} ({:.0f}%) \t Loss: {:.6f}'.format((1+batch_idx) * len(data), len(train_loader.dataset), 100. * batch_idx / len(train_loader), loss.item()))
  loss_train.append(loss.item())

  ####### Evaluation Mode #######
  model.eval()
  print('\nTest Epoch {}'.format(epoch+1))

  y_valid_pred = []
  loss = 0
  correct = 0

  with torch.no_grad(): # disable gradient calculation.
    for valid_idx, (data, target, index) in enumerate(valid_loader):
        output = model(data)                          # (batch_size) by (num_class)
        loss += criterion(output, target).item() # sum up batch loss
        pred = output.max(dim = 1)[1]                 # get the predicted class labels
        y_valid_pred.append(pred)
        correct += pred.eq(target).sum().item()       # get the correct number of class labels
        

  loss /= len(valid_loader)
  loss_valid.append(loss)
  print('Accuracy: {}/{} ({:.2f}%) \tLoss: {:.6f}\n'.format(correct, len(valid_loader.dataset), 100. * correct / len(valid_loader.dataset), loss))
  print('------------------------------------------------')

print('Evaluation Completed.')
print('Total Epoch: {} \tBatch Size: {} \tInput Size: {}'.format(epoch+1, BatchSize, '50x25'))

# Net 저장
PATH = 'C:/Study2019/Win32/changetocpp/Project3/9202.pth'
torch.save(model.state_dict(), PATH)
