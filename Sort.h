#pragma once

constexpr int THRESHOLD = 28;

template<typename T, typename Compare>
void insertionSort(T* const first, T* const last, Compare comp) {
	if (first == nullptr || last == nullptr || last <= first) return;
	T* const arr = first;
	int n = last - first + 1;
	for (int i = 1; i < n; i++) {
		if (!comp(arr[i], arr[i - 1])) {
			continue;
		}
		T element = std::move(arr[i]);
		int j = i - 1;
		while (j >= 0 && comp(element, arr[j])) {
			arr[j + 1] = std::move(arr[j]);
			j--;
		}
		arr[j + 1] = std::move(element);
	}
}

template<typename T, typename Compare>
static T* calcPivot(T& o1, T& o2, T& o3, Compare comp) {
	T& l = comp(o1, o2) ? o1 : o2;
	T& r = comp(o1, o2) ? o2 : o1;

	if (comp(o3, l)) {
		return &l;
	}
	if (comp(r, o3)) {
		return &r;
	}
	return &o3;
}

template <typename T, typename Compare>
static int createPartition(T* arr, int l, int r, T pivot, Compare comp) {
	while (true) {
		while (comp(arr[l], pivot)) {
			l++;
		}
		while (comp(pivot, arr[r])) {
			r--;
		}
		if (l >= r) {
			return r;
		}
		std::swap(arr[l], arr[r]);
		l++;
		r--;
	}
}



template<typename T, typename Compare>
void sort(T* arr, int l, int r, Compare comp) {
	if (r <= l) return;
	while (r - l + 1 > THRESHOLD) {
		int length = r - l + 1;
		T* pivot = calcPivot(arr[l], arr[(r - l) / 2], arr[r], comp);
		int mid = createPartition(arr, l, r, *pivot, comp);

		if (mid - l + 1 > r - mid) {
			sort(arr, mid + 1, r, comp);
			r = mid;

		}
		else {
			sort(arr, l, mid, comp);
			l = mid + 1;
		}
	}
	insertionSort(arr + l, arr + r, comp);
}

template<typename T, typename Compare>
void sort(T* first, T* last, Compare comp) {
	if (first == nullptr || last == nullptr || last <= first) {
		return;
	}
	sort(first, 0, last - first - 1, comp);
}

