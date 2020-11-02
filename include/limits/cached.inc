
limit_req zone=reqlim burst=100 nodelay;
limit_req zone=hostreqlim burst=200;
