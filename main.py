#!/usr/bin/python3.9

import epics
from MS import XRD

if __name__ == "__main__":

    x = XRD(["IOCs/MS_DAQ/db/MS_UI_settings.req"], {"$(P)":"MS:", "$(N)":list(range(1, 41))})
