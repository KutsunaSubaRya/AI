# -*- coding: utf-8 -*-

from numpy import *

def sigmoid(x):
    return 1 / (1 + exp(-(x)))

train_in_tmp = array([[10, 77,63.5,58.5,78,82,73,65],
                    [8, 82.5,75.5,87.5,82.5,75,99,91],
                    [11, 91,89,88.5,89.75,105,97,114],
                    [11, 94.5,89.5,95.5,90.5,93,116,112],
                    [6, 78.25,63.5,62.5,67.25,94,66,77],
                    [5, 86.5,90.5,82.5,0,85,94,90],
                    [10, 89,77.5,90,90.5,95,105,97],
                    [8, 91.25,90.5,88.5,0,83,83,60],
                    [7, 84,0,0,0,65,0,0],
                    [11, 64,9,0,0,85,48,71]])
train_in = train_in_tmp/116
train_sol_tmp = array([[79,85,95,96,75,75,91,76,44,57]]).T
train_sol = train_sol_tmp/116
# initialize nn_weights
random.seed(1)
nn_weights = 2*random.random((8,1))-1
nn_2_weights = 2*random.random((1,1))-1
print("random nn_weight=")
print(nn_weights)
bias_tmp1 = random.random()
bias1 = full((10,1),bias_tmp1)
bias_tmp2 = random.random()
bias2 = full((10,1),bias_tmp2)
print("bias1=")
print(bias1)
print("bias2=")
print(bias2)
# train the network
for i in range(2000):
    # print("\n i= ", i, "nn_weight=")
    # print(nn_weights)
    # Calculate the outputs for each training examples
    train_out = sigmoid(dot(train_in, nn_weights)+bias1)
    train_out2 = sigmoid(dot(train_out, nn_2_weights)+bias2)
    # print("train_out2 =")
    # print(train_out2)
    # Run the NN adjustments 
    error = (train_sol - train_out2) * train_out2 * (1 - train_out2)
    nn_2_weights += dot(train_out.T, error)
    bias2 += error

    error = dot(error, nn_2_weights.T) * train_out * (1 - train_out)
    nn_weights += dot(train_in.T, error)
    bias1 += error

print("nn_weight=")
print(nn_weights)
print("train_out =")
print(train_out)

#unknown test input 1
test_in_1_tmp = array([11, 86,90,93.5,93,90,99,106])
test_in_1 = test_in_1_tmp/116
# Print the result for our unknown test input 
print('\nThe final prediction is ',sigmoid(sigmoid(dot(test_in_1, nn_weights)+bias_tmp1)*nn_2_weights+bias_tmp2)*116)
#unknown test input 2
test_in_2_tmp = array([11, 85.5,70,86.5,88.5,91,88,90])
test_in_2 = test_in_2_tmp/116
# Print the result for our unknown test input 
print('\nThe final prediction is ',sigmoid(sigmoid(dot(test_in_2, nn_weights)+bias_tmp1)*nn_2_weights+bias_tmp2)*116)
#unknown test input 3
test_in_3_tmp = array([11, 85,62,63,84.5,96,95,74])
test_in_3 = test_in_3_tmp/116
# Print the result for our unknown test input 
print('\nThe final prediction is ',sigmoid(sigmoid(dot(test_in_3, nn_weights)+bias_tmp1)*nn_2_weights+bias_tmp2)*116)
#unknown test input 4
test_in_4_tmp = array([7, 70.5,61.5,59,52,98,95,38])
test_in_4 = test_in_4_tmp/116
# Print the result for our unknown test input 
print('\nThe final prediction is ',sigmoid(sigmoid(dot(test_in_4, nn_weights)+bias_tmp1)*nn_2_weights+bias_tmp2)*116)