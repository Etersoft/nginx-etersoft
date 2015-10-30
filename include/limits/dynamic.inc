
limit_req zone=reqlim burst=10 nodelay;
limit_req zone=hostreqlim burst=40;
