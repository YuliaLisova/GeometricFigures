#ifndef Point_H
#define  Point_H


class Point
{
public:
	int x_;
	int y_;

	Point()
	{
		x_ = y_ = 0;
	}
	void SetPoint(int x, int y)
	{
		x_ = x;
		y_ = y;
	}
};

#endif