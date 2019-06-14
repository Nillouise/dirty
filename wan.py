match = pd.read_csv("match.csv")


#check
match[match.apply(lambda x:(x['red team2'] + x['blue team2']).count('VICTORY',axis = 1) == 0]['url']
match['team kill'].apply(lambda x:x.count('.')).sum()
match['blue team gold'].apply(lambda x:x.count('.')).sum()

blue_player_column = ['blue player%d name'%i for i in range(1,6)]
red_plyaer_column = ['red player%d name'%i for i in range(1,6)]

playerwinrate_column = ["playerwinrate"+str(i) for i in range(10)]


from datetime import datetime

def convert_time(x):
    try:
        return datetime.strptime(" ".join(x.split(" ")[:-1]),'%Y-%m-%d %H:%M')
    except:
        return None
        
match['start_time].apply(convert_time)
data = match[blue_player_column + red_plyaer_column]
data['start_time'] = match['start_time'].apply(convert_time)
data['res'] = match.apply(lambda x: float(x['blue team2'].count('VICTORY')),axis=1)

data = data.dropna()
data = data.set_index('start_time')

#add player win rate
player_win = pd.DataFrame(columns = 'a','result'])
for i in blue_player_column:
    player_win = player_win.append(data[[i,'res']].rename(columns = {i:'a','res':'result'}))
   
for i in red_plyaer_column:
    tmp = data[[i,'res']].rename(columns = {i:'a','res':'result'})
    tmp['result'] = 1-tmp['result']
    player_win = player_win.append(tmp)
   
player_win = player_win.sort_index()

grp_player_win = player_win.groupby(['a']).filter(lambda x:x['result'].count()>30).groupby(['a'])['result'].mean()

for index,i in  enumerate(blue_player_column+ red_plyaer_column):
    data['playerwinrate'+str(index)] = data[blue_player_column + red_plyaer_column].apply(lambda x:grp_player_win.get((x[i]),0.45),axis=1)
    

player_win = player_win.reset_index()

#view
player_win[player_win['a'] =='YaGao'].reset_index()['result'].rolling(50).mean().plot()


#serven predict
y_only_period = data['res']
X_only_period = pd.get_dummies(data[playerwinrate_column])
X_train








