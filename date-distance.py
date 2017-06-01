# Calculate time distance between 2 days
from datetime import datetime as dt
day1=dt(2017,6,1)
day2=dt(2017,6,2)
print(abs((day1-day2).days))
