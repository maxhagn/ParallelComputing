#!/usr/bin/env python 

time_small_p1 = list()
time_small_p2 = list()
time_small_p4 = list()
time_small_p8 = list()
time_small_p11 = list()
time_small_p16 = list()
time_small_p32 = list()


time_medium_p1 = list()
time_medium_p2 = list()
time_medium_p4 = list()
time_medium_p8 = list()
time_medium_p11 = list()
time_medium_p16 = list()
time_medium_p32 = list()

time_large_p1 = list()
time_large_p2 = list()
time_large_p4 = list()
time_large_p8 = list()
time_large_p11 = list()
time_large_p16 = list()
time_large_p32 = list()

with open('results.txt') as f:
    lines = f.readlines()


for line in lines:
    if line[0] == 'p': 
        continue    
    else :
        if line[9] == ',':
            if line[0] == '1':
                time_small_p1.append(line[-9:len(line)-1])
            elif line[0] == '2':
                time_small_p2.append(line[-9:len(line)-1])
            elif line[0] == '4':
                time_small_p4.append(line[-9:len(line)-1])
            elif line[0] == '8':
                time_small_p8.append(line[-9:len(line)-1])
        if line[10] == ',':
            if line[0] == '1' and line[1] == '1':
                time_small_p11.append(line[-9:len(line)-1])
            elif line[0] == '1' and line [1] == '6':
                time_small_p16.append(line[-9:len(line)-1])
            elif line[0] == '3' and line [1] == '2':
                time_small_p32.append(line[-9:len(line)-1])
            elif line[0] == '1':
                time_medium_p1.append(line[-9:len(line)-1])
            elif line[0] == '2':
                time_medium_p2.append(line[-9:len(line)-1])
            elif line[0] == '4':
                time_medium_p4.append(line[-9:len(line)-1])
            elif line[0] == '8':
                time_medium_p8.append(line[-9:len(line)-1])
        if line[11] == ',':
            if line[0] == '1' and line[1] == '1':
                time_medium_p11.append(line[-9:len(line)-1])
            elif line[0] == '1' and line [1] == '6':
                time_medium_p16.append(line[-9:len(line)-1])
            elif line[0] == '3' and line [1] == '2':
                time_medium_p32.append(line[-9:len(line)-1])
            elif line[0] == '1':
                time_large_p1.append(line[-9:len(line)-1])
            elif line[0] == '2':
                time_large_p2.append(line[-9:len(line)-1])
            elif line[0] == '4':
                time_large_p4.append(line[-9:len(line)-1])
            elif line[0] == '8':
                time_large_p8.append(line[-9:len(line)-1])
        if line[12] == ',':
            if line[0] == '1' and line[1] == '1':
                time_large_p11.append(line[-9:len(line)-1])
            elif line[0] == '1' and line [1] == '6':
                time_large_p16.append(line[-9:len(line)-1])
            elif line[0] == '3' and line [1] == '2':
                time_large_p32.append(line[-9:len(line)-1])

medians_small_input = list()
medians_small_input.append(sum([float(x) for x in time_small_p1])/len(time_small_p1))
medians_small_input.append(sum([float(x) for x in time_small_p2])/len(time_small_p2))
medians_small_input.append(sum([float(x) for x in time_small_p4])/len(time_small_p4))
medians_small_input.append(sum([float(x) for x in time_small_p8])/len(time_small_p8))
medians_small_input.append(sum([float(x) for x in time_small_p16])/len(time_small_p16))
medians_small_input.append(sum([float(x) for x in time_small_p32])/len(time_small_p32))


medians_medium_input = list()
medians_medium_input.append(sum([float(x) for x in time_medium_p1])/len(time_medium_p1))
medians_medium_input.append(sum([float(x) for x in time_medium_p2])/len(time_medium_p2))
medians_medium_input.append(sum([float(x) for x in time_medium_p4])/len(time_medium_p4))
medians_medium_input.append(sum([float(x) for x in time_medium_p8])/len(time_medium_p8))
medians_medium_input.append(sum([float(x) for x in time_medium_p16])/len(time_medium_p16))
medians_medium_input.append(sum([float(x) for x in time_medium_p32])/len(time_medium_p32))


medians_large_input = list()
medians_large_input.append(sum([float(x) for x in time_large_p1])/len(time_large_p1))
medians_large_input.append(sum([float(x) for x in time_large_p2])/len(time_large_p2))
medians_large_input.append(sum([float(x) for x in time_large_p4])/len(time_large_p4))
medians_large_input.append(sum([float(x) for x in time_large_p8])/len(time_large_p8))
medians_large_input.append(sum([float(x) for x in time_large_p16])/len(time_large_p16))
medians_large_input.append(sum([float(x) for x in time_large_p32])/len(time_large_p32))

print('median of small input:[1,2,4,16,32]:{}'.format(medians_small_input))
print('median of medium input:[1,2,4,16,32]:{}'.format(medians_medium_input))
print('median of large input:[1,2,4,16,32]:{}'.format(medians_large_input))

speedup_small_input = list()
speedup_medium_input = list()
speedup_large_input = list()
for i in range(1, 6):
    speedup_small_input.append(medians_small_input[0] / medians_small_input[i])
    speedup_medium_input.append(medians_medium_input[0] / medians_medium_input[i])
    speedup_large_input.append(medians_large_input[0] / medians_large_input[i])

print('speedup for small input [2,4,8,11,16,32]:{}'.format(speedup_small_input))
print('speedup for medium input [2,4,8,11,16,32]:{}'.format(speedup_medium_input))
print('speedup for large input [2,4,8,11,16,32]:{}'.format(speedup_large_input))

