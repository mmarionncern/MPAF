from keras.models import Sequential
from keras.layers import Dense, Activation
from keras.layers import LSTM
from keras.optimizers import RMSprop
from keras.callbacks import LambdaCallback
from keras.utils.data_utils import get_file
import simplejson
import numpy as np
import random
import sys
import ROOT

from NNFunctions import *


def evaluateModel(event, model):
    res=evaluateModel(evt,model)
    return res[0]

