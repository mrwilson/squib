.load ./squib

create table input (x integer, y integer);
insert into input values(1,1);
insert into input values(2,2);

select
  case when pearson(x,y) = 1.0 then
    "SUCCESS"
  else
    pearson(x,y)
  end
  from input;
