import os
import re
import matplotlib.pyplot as plt
from scipy.ndimage import gaussian_filter1d

num_size = range(10, 1000011, 10000)


def get_command(comm):
    return os.popen(comm).read().split("\n")


def extract_time(comm_list, number):
    pattern = r'(\d+\.\d+) milliseconds'
    q_sort = re.search(pattern, comm_list[5])
    my_sort = re.search(pattern, comm_list[7])
    q_sort_time = float(q_sort.group(1)) if q_sort else None
    my_sort_time = float(my_sort.group(1)) if my_sort else None
    return number, q_sort_time, my_sort_time


def time_list():
    x = []
    q_sort_y = []
    my_sort_y = []
    for i in num_size:
        command = "./quick-sort " + ("%s" % i)
        time = extract_time(get_command(command), i - 10)
        x.append(time[0] / 1000)
        q_sort_y.append(time[1])
        my_sort_y.append(time[2])
        print(time)
    q_sort_y_smooth = gaussian_filter1d(q_sort_y, sigma=5)
    my_sort_y_smooth = gaussian_filter1d(my_sort_y, sigma=5)
    return x, q_sort_y_smooth, my_sort_y_smooth


def plot(x, y1, y2):
    plt.title('Comparison of Quicksort and Random Quicksort')
    plt.xlabel('Size of input array(10k)')
    plt.ylabel('Time(ms)')
    plt.grid(True)
    plt.plot(x, y1, label='Quicksort')
    plt.plot(x, y2, label='Random Quicksort')
    plt.legend()
    plt.ticklabel_format(style='plain')

    plt.show()


if __name__ == '__main__':
    coordinate = time_list()
    plot(coordinate[0], coordinate[1], coordinate[2])
