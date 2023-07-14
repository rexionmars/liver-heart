import pandas as pd
import numpy as np

from glob import glob
from PIL import Image

import easyocr



annot = pd.read_parquet('../media_train/TR/annot.parquet')
imgs = pd.read_parquet('../media_train/TR/img.parquet')
img_fns = glob('../media_train/TR/train_val_images/train_images/*')

reader = easyocr.Reader(['en'], gpu = True)
results = reader.readtext(img_fns[11])
pd.DataFrame(results, columns=['bbox','text','conf'])
