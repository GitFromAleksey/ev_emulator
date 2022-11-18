import matplotlib.pyplot as plt
import numpy as np
import re
import json
import csv

##FILE_NAME = 'YAT-Log-20221118-135653.log'
##FILE_NAME = 'YAT-Log-20221118-142231.log'
FILE_NAME = 'YAT-Log-20221118-134502.log'

RE_JSON_CONTENT = '{.+}'

def GetRawFileContent(file_name):
    with open(file_name, encoding='utf-8') as f:
        lines = f.readlines()
        return lines
    return None

def RawDataProcessing(raw_data_lines):
    data_lines = []
    for line in raw_data_lines:
        match = re.search(RE_JSON_CONTENT,line)
        if match:
            data_lines.append(match[0])
    return data_lines

def main():
    raw_file_content = GetRawFileContent(FILE_NAME)

    json_lines = RawDataProcessing(raw_file_content)

    TIME_MS = []
    EV_STATE = []
    CP_VAL = []
    CP_DUTY = []
    PP_VAL = []
    for j in json_lines:
##        print(j)
        TIME_MS.append(json.loads(j)['TIME_MS'])
        EV_STATE.append(json.loads(j)['EV_STATE'])
        CP_VAL.append(json.loads(j)['CP_VAL']/1000)
        CP_DUTY.append(json.loads(j)['CP_DUTY']/100)
        PP_VAL.append(json.loads(j)['PP_VAL']/1000)
        
    fig, ax = plt.subplots()
##    ax.plot(TIME_MS, EV_STATE, label = 'EV_STATE')
    ax.plot(TIME_MS, CP_VAL, label = 'CP_VAL')
    ax.plot(TIME_MS, CP_DUTY, label = 'CP_DUTY')
    ax.plot(TIME_MS, PP_VAL, label = 'PP_VAL')

    plt.legend()
    plt.text(60, .025, r'$\mu=100,\ \sigma=15$')
    plt.title('EV charge signals sequence')
    plt.xlabel('time, ms')
    plt.ylabel('signals')
    plt.grid(True)
    plt.show()

if __name__ == '__main__':
    main()
