#!/usr/bin/python
import sys
import mlt_pb2
import numpy as np
import random
from PIL import Image
from PIL import ImageDraw
import matplotlib.pyplot as plt
from matplotlib import pyplot
import os.path, os

def readlabel(filename, label):
    """
    Read a label file
    """
    try:
        with open(filename, "rb") as f:
            label.ParseFromString(f.read())
            if label.version() != "v0.3":
                print 'File version error'
                return
    except IOError as err:
        print 'File Error: ' + str(err)

def main():
    print "Main is runing!"
    database = "F:\\database\\label\\"
    datapath = "001-001.wrl\\"
    filepath = "000_2016y4m28d.wlb"
    oldroot = "F:/"
    newroot = "/"

    imglistName = "train.txt"
    f = open(imglistName,"w")
    f.truncate()
    f.close()


    labels = np.zeros((12088, 68 * 5),dtype = np.float32)
    #datas = np.zeros((12500, 385, 474, 3),dtype = np.float)
    ii = 0
    cc = 0
    label = mlt_pb2.Label()
    for d in range(1, 101):
        n = str(d)
        s = n.zfill(3)
        datapath = s + "-001.wrl\\"
        for i in range(0,5):
            for j in range(0,5):
                for k in range(0,5):
                    n = str(i*100+j*10+k)
                    s = n.zfill(3)
                    filepath = s + "_2016y4m28d.wlb"
                    filename = database + datapath + filepath
                    print filename
                    with open(filename, "rb") as f:
                        label.ParseFromString(f.read())
                        if label.version != u"v0.3":
                            print "File version error, program break!"
                            return
                    label_list = ()
                    pointCount = 0
                    for point in label.point:
                        pointCount += 1
                        if point.id >= 0 and point.id < 68:
                            point_positon = (point.x, point.y)
                            point_deepth = (point.xl, point.yl, point.zl)
                            label_list = label_list + point_positon + point_deepth
                    if pointCount!=68:
                        #ii += 1
                        continue
                    labels[ii, :] = np.array(label_list).astype(np.float32)
                    del label_list       
                    #im = Image.open(label.imgFileName)
                    #datas[iii, :, :, :] = np.array(Image.open(label.imgFileName)).astype(np.float32)/256
                        #print datas[ii, :, 200, 0]
                    name = label.imgFileName
                    name = name.replace("\\","/")
                    name = name.replace(oldroot, newroot, 1)
                    with open(imglistName,"a") as out:
                        out.write(name + " \t0\n")
                    ii += 1
                    print ii
                    
    np.save("train_labels.npy",labels)
    print "Trainset Done."

    imglistName = "test.txt"
    f = open(imglistName,"w")
    f.truncate()
    f.close()

    labels = np.zeros((2806, 68 * 5),dtype = np.float32)
    #datas = np.zeros((12500, 385, 474, 3),dtype = np.float)
    ii = 0
    cc = 0
    label = mlt_pb2.Label()
    for d in range(101, 124):
        n = str(d)
        s = n.zfill(3)
        datapath = s + "-001.wrl\\"
        for i in range(0,5):
            for j in range(0,5):
                for k in range(0,5):
                    n = str(i*100+j*10+k)
                    s = n.zfill(3)
                    filepath = s + "_2016y4m28d.wlb"
                    filename = database + datapath + filepath
                    print filename
                    with open(filename, "rb") as f:
                        label.ParseFromString(f.read())
                        if label.version != u"v0.3":
                            print "File version error, program break!"
                            return
                        """
                        Create Label
                        """
                    label_list = ()
                    pointCount = 0
                    for point in label.point:
                        pointCount += 1
                        if point.id >= 0 and point.id < 68:
                            point_positon = (point.x, point.y)
                            point_deepth = (point.xl, point.yl, point.zl)
                            label_list = label_list + point_positon + point_deepth
                    if pointCount!=68:
                        #ii += 1
                        continue
                    labels[ii, :] = np.array(label_list).astype(np.float32)
                    del label_list       
                        
                    #im = Image.open(label.imgFileName)
                    #datas[iii, :, :, :] = np.array(Image.open(label.imgFileName)).astype(np.float32)/256
                        #print datas[ii, :, 200, 0]
                    name = label.imgFileName
                    name = name.replace("\\","/")
                    name = name.replace(oldroot, newroot, 1)
                    with open(imglistName,"a") as out:
                        out.write(name + " \t0\n")
                    ii += 1
                    print ii

    np.save("test_labels.npy",labels)
    print "Testset Done."                    

if __name__ == '__main__':
    main()
