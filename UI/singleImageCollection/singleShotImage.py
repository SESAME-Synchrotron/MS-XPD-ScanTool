#!/usr/bin/python3.9

import os
import sys
import time
import argparse
import numpy as np
from PIL import Image
from epics import PV

timeout = 1
PV_Prefixes = ["ID09EH-DCA-FLIR02:AI-CAM2-SIDE", "ID09EH-DCA-FLIR01:AI-CAM1-UP"]
category = {"up": "diffractometer", "side": "container"}

acquirePV = ":Acquire"
arrayDataPV = ":image1:ArrayData"
sizeX_PV, sizeY_PV = ":ArraySizeX_RBV", ":ArraySizeY_RBV"
enableCallbackPV = ":EnableCallbacks"
arrayCallbackPV = ":ArrayCallbacks"
triggerSourcePV = ":TriggerSource"
expTimePV = ":AcquireTime"
classLabelPV = "classLabel"
lightConditionPV = "lightCondition"
extensionPV = "extension"
ROIs = 4
fileOpened = False

def capture(PV_Prefix, saveImage):
    """
    Capture:
    - stop acquiring
    - reshape image
    """

    PV(PV_Prefix + acquirePV).put(0, wait=True)

    if saveImage == "Y":
        reshape(PV_Prefix)
    else:
        print("image capturing completed!")

def reshape(PV_Prefix):
    """
    Reshape:
    - reshape the arrayData (1D) to the specified ROIs dimensions (2D)
    - crop image
    - save cropped image
    """

    image = PV(PV_Prefix.split(":")[0] + arrayDataPV).get(timeout=timeout, use_monitor=False)
    sizeX = PV(PV_Prefix + sizeX_PV).get(timeout=timeout, use_monitor=False)
    sizeY = PV(PV_Prefix + sizeY_PV).get(timeout=timeout, use_monitor=False)
    expTime = PV(PV_Prefix + expTimePV).get(timeout=timeout, use_monitor=False)
    ROIPrefix = f"{PV_Prefix.split('-')[-1].lower()}CamROI"

    print(f"reshaping image to {sizeX} X {sizeY}")

    reshapedArray = np.reshape(image, (sizeY, sizeX))
    reshapedArray = np.flipud(reshapedArray)
    camera = category[f"{PV_Prefix.split('-')[-1].lower()}"]
    save(reshapedArray, camera, str(expTime).replace('.', 'p'))

    for ROI in range(1, ROIs+1):
        x1 =  PV(f"{ROIPrefix}{ROI}:x1").get(timeout=timeout, use_monitor=False)
        x2 =  PV(f"{ROIPrefix}{ROI}:x2").get(timeout=timeout, use_monitor=False)
        y1 =  PV(f"{ROIPrefix}{ROI}:y1").get(timeout=timeout, use_monitor=False)
        y2 =  PV(f"{ROIPrefix}{ROI}:y2").get(timeout=timeout, use_monitor=False)
        croppedImage = reshapedArray[y1:y1+y2,x1:x1+x2]
        if not croppedImage.size == 0:
        	print("\nImage shape:", croppedImage.shape)
        	save(croppedImage, camera, f"R{ROI}_{str(expTime).replace('.', 'p')}", frameType='cropped')
    # except:
    #     print("Couldn't reshape the image, please check the image dimensions!")

def save(frame, camera, ROI, frameType='original'):
    """
    Save:
    - save the array as image
    """
    global fileOpened
    base = "/home/control/AIProject/data"
    classLabel = PV(classLabelPV).get(timeout=timeout, use_monitor=False, as_string=True)

    if frameType == "original":
    	filePath = "/home/control/MS-XPD-ScanTool/UI/singleImageCollection/.originalSequence.txt"
    else:
    	filePath = "/home/control/MS-XPD-ScanTool/UI/singleImageCollection/.croppedSequence.txt"

    with open(filePath, "r") as file:
        lines = file.readlines()
    empty = [line.strip() for line in lines if line.strip()]
    lastLine = empty[-1] if empty else ''
    lastLine = empty[-2] if fileOpened else empty[-1]

    ROI = ROI
    lightCondition = PV(lightConditionPV).get(timeout=timeout, use_monitor=False, as_string=True)
    imageExtension = PV(extensionPV).get(timeout=timeout, use_monitor=False, as_string=True)
    if frameType == "original":
    	fullPath = f"{base}/{camera}/{classLabel}/Original/{lastLine}_original_{ROI}_{lightCondition}{imageExtension}"
    else:
    	fullPath = f"{base}/{camera}/{classLabel}/{lastLine}_{ROI}_{lightCondition}{imageExtension}"

    frame = frame.astype(np.uint8)
    image = Image.fromarray(frame)
    print(f"saving image to {fullPath}")
    try:
        image.save(fullPath)
        print(f"image has been saved!")
        if not frameType == "original":
	        if not fileOpened:
		        with open(filePath, "a") as file:
		            file.write(f"\n{int(lastLine) + 1}")
		            fileOpened = True
        else:
	        with open(filePath, "a") as file:
	            file.write(f"\n{int(lastLine) + 1}")
    except:
        print("Couldn't save the image, please check the image path!")


if __name__ == "__main__":

    parser = argparse.ArgumentParser(description="Single Frame Acquisition")
    parser.add_argument('--detectorPVPrefix', type=str, help=' -> ID09EH-DCA-FLIR01:AI-CAM1-UP, ID09EH-DCA-FLIR02:AI-CAM2-SIDE')
    parser.add_argument('--saveImage', type=str, default="Yes", help=' -> Yes, No')

    args = parser.parse_args()
    detector = args.detectorPVPrefix.strip().upper()
    saving = args.saveImage

    if detector in PV_Prefixes:
        PV(detector + enableCallbackPV).put(1, wait=True)
        PV(detector + arrayCallbackPV).put(1, wait=True)
        PV(detector + triggerSourcePV).put(0, wait=True)
        capture(detector, saving[0].capitalize())

    else:
        print(f"{detector} is not correct PV prefix!!!")
        sys.exit()