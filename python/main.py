#!/usr/bin/env python
import numpy as np
import h5py

def save_data_as_hdf5(hdf5_data_filename,np_filename):
    '''
    HDF5 is one of the data formats Caffe accepts
    example:
    def save_data_as_hdf5(hdf5_data_filename, data)
    with h5py.File(hdf5_data_filename, 'w') as f:
        f['data'] = data['input'].astype(np.float32)
        f['label'] = data['output'].astype(np.float32)
    '''
    
    with h5py.File(hdf5_data_filename, 'w') as f:
        f['label'] = np.load(np_filename)

def main():
    save_data_as_hdf5("train_label.hdf5","/usr/database/train_labels.npy")
    save_data_as_hdf5("test_label.hdf5","/usr/database/test_labels.npy")

if __name__ == '__main__':
    main()