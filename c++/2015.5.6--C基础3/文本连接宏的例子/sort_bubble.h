#ifndef _SORT_BUBBLE_H_
#define _SORT_BUBBLE_H_

#define sort_bubble_declear(type) \
	void sort_bubble_##type (type* p, int n);

#define sort_bubble_define(type) \
	void sort_bubble_##type (type* p, int n) \
	{ \
		for (int i = n - 1; i > 0; --i) \
		{ \
			for (int j = 0; j < i; ++j) \
			{ \
				if (p[j] > p[j + 1]) \
				{ \
					type t = p[j]; \
					p[j] = p[j + 1]; \
					p[j + 1] = t; \
				} \
			} \
		} \
	}

#endif