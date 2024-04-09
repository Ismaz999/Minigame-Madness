from image import *
import cv2 as cv
import numpy

refreshRate = 10

montyTexture = None

def setup():
    global montyTexture
    global montytemplate
    montyTexture = cv.imread('assets/Whack a Monty/Monty.png')
    montytemplate = cv.imread('assets/Whack a Monty/template_monty.png')
def update():
    # subScreen = getScreenshot(mainScreen=False)
    subScreen = pyautogui.screenshot(region=(960,192, 1080, 720))

    subScreen_opencv = numpy.array(subScreen)
    subScreen_opencv = subScreen_opencv[:, :, ::-1].copy()

    locatedMontyBounds = None

    method = cv.TM_CCORR_NORMED

    montyresult= cv.matchTemplate(subScreen_opencv,montytemplate,method)
    min_val, max_val, min_loc, max_loc = cv.minMaxLoc(montyresult)
    print(max_loc)


    locatedMontyBounds = (max_loc[0]+(montytemplate.shape[0]/2)+960,max_loc[1]+(montytemplate.shape[1]/2)+192)
    print(locatedMontyBounds)


    # If a monty is located, then click on it.
    if locatedMontyBounds is not None:
        # boundCenter = pyautogui.center(locatedMontyBounds)
        # montyPosition = localToGlobalPosition(boundCenter, mainScreen=False)

        pyautogui.moveTo(locatedMontyBounds[0], locatedMontyBounds[1], _pause=False)
        pyautogui.drag(0, 1, 0.11, _pause=False)