#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <utility>
#include <Windows.h>
#include "../puzzle_switch.h"

void day01()
{
	/* Part 1 
	FILE* fin;
	fopen_s(&fin, "input_day01.txt", "r");

	if(fin == NULL)
		return;

	const unsigned int BUFFER_SIZE = 32;
	char buf[BUFFER_SIZE];
	int result = 0;

	while(fgets(buf, BUFFER_SIZE, fin) != NULL)
	{
		result += atoi(buf);
	}

	fclose(fin);
	printf("%i\n", result);

	/*/
	FILE* fin;
	fopen_s(&fin, "input_day01.txt", "r");

	if(fin == NULL)
		return;

	const uint32_t BUFFER_SIZE = 32;
	char buf[BUFFER_SIZE];

	uint32_t pos_size = 100, neg_size = 100;
	bool *visited_pos = (bool*)calloc(pos_size, sizeof(bool)),
		*visited_neg = (bool*)calloc(neg_size, sizeof(bool));

	int result = 0;
	while(true)
	{
		bool **target;
		unsigned int index;
		unsigned int* size;

		if(result < 0)
		{
			target = &visited_neg;
			index = (result * -1) - 1;
			size = &neg_size;
		}
		else
		{
			target = &visited_pos;
			index = result;
			size = &pos_size;
		}

		while (index >= *size)
		{
			*target = (bool*)realloc(*target, *size * 2);
			memset((*target + *size), 0, *size);
			*size *= 2;
		}

		if((*target)[index])
			break;

		(*target)[index] = true;

		if(fgets(buf, BUFFER_SIZE, fin) == NULL)
		{
			fseek(fin, 0, SEEK_SET);
			fgets(buf, BUFFER_SIZE, fin);
		}

		result += atoi(buf);
	}

	fclose(fin);
	printf("%i\n", result);

	free(visited_pos);
	free(visited_neg);

	//*/
}

void day02()
{
	/* Part 1
	FILE* fin;
	fopen_s(&fin, "input_day02.txt", "r");

	if(fin == NULL)
		return;

	int twice_count = 0, thrice_count = 0;

	const unsigned int BUF_SIZE = 28;
	char buf[BUF_SIZE];
	
	while(fgets(buf, BUF_SIZE, fin))
	{
		qsort(buf, BUF_SIZE, sizeof(char), [](const void *e1, const void *e2) -> int
		{
			char a = *((char*)e1), b = *((char*)e2);
			if(a < b) return -1;
			if(a > b) return 1;
			return 0;
		});

		bool has_twice = false, has_thrice = false;

		for(int i = 0; i < BUF_SIZE - 2; ++i)
		{
			int j = 1;
			while(buf[j + i] == buf[i])
				j++;

			if(j == 2)
				has_twice = true;
			else if(j == 3)
				has_thrice = true;

			i += (j - 1);
		}

		if(has_twice)
			++twice_count;
		if(has_thrice)
			++thrice_count;
	}

	fclose(fin);
	printf("Twice: %i\nThrice: %i\nChecksum: %i\n", twice_count, thrice_count, twice_count * thrice_count);
	/*/

	FILE* fin;
	fopen_s(&fin, "input_day2.txt", "r");

	if(fin == NULL)
		return;

	const unsigned int BUF_SIZE = 28;
	const unsigned int CODE_COUNT = 250;

	char codes[CODE_COUNT][BUF_SIZE];
	int i = 0;
	while(fgets(codes[i], BUF_SIZE, fin))
		++i;

	fclose(fin);

	int j;
	for(i = 0; i < CODE_COUNT; ++i)
	{
		for(j = i; j < CODE_COUNT; ++j)
		{
			int differ_count = 0;
			for(int k = 0; k < BUF_SIZE; ++k)
			{
				if(codes[i][k] != codes[j][k])
				{
					++differ_count;
					if(differ_count > 1)
						break;
				}
			}

			if (differ_count != 1)
				continue;

			// Found the match
			goto break_;
		}
	}
break_:

	char in_common[BUF_SIZE];
	for(int k = 0; k < BUF_SIZE; k++)
	{
		if(codes[i][k] == codes[j][k])
			in_common[k] = codes[i][k];
		else
			in_common[k] = ' ';
	}

	printf("%s\n", in_common);

	//*/
}

void day03()
{
	/* Part 1
	FILE* fin;
	fopen_s(&fin, "input_day03.txt", "r");

	if(fin == NULL)
		return;

	uint8_t fabric[1000][1000] = { 0 };
	uint32_t overlap_count = 0;

	const uint32_t BUF_SIZE = 25;
	char line[BUF_SIZE];

	while(fgets(line, BUF_SIZE, fin))
	{
		int id, left, top, width, height;
		sscanf_s(line, "#%i @ %i,%i: %ix%i", &id, &left, &top, &width, &height);

		for(int x = left; x < left + width; ++x)
		{
			for(int y = top; y < top + height; ++y)
			{
				if(fabric[x][y] == 1)
					++overlap_count;

				++fabric[x][y];
			}
		}
	}

	printf("Overlap count: %i\n", overlap_count);
	fclose(fin);
	
	/*/

	FILE* fin;
	fopen_s(&fin, "input_day3.txt", "r");

	if(fin == NULL)
		return;

	const uint32_t BUF_SIZE = 25;
	char line[BUF_SIZE];

	int32_t* fabric = (int32_t *)calloc(1000 * 1000, sizeof(int32_t));

	struct claim {
		int id, left, top, width, height;
	};
	claim* claims = (claim*)calloc(1350, sizeof(claim));
	int claim_count = 0;

	while(fgets(line, BUF_SIZE, fin))
	{
		claim* c = claims + claim_count;
		sscanf_s(line, "#%i @ %i,%i: %ix%i", 
			&c->id, 
			&c->left, 
			&c->top, 
			&c->width, 
			&c->height);

		for(int x = c->left; x < c->left + c->width; ++x)
		{
			for(int y = c->top; y < c->top + c->height; ++y)
			{
				if(fabric[x * 1000 + y] == 0)
					fabric[x * 1000 + y] = c->id;
				else
					fabric[x * 1000 + y] = -1;
			}
		}

		++claim_count;
	}
	fclose(fin);

	claim* c;
	for(c = claims; c < claims + claim_count; ++c)
	{
		bool valid = true;

		for(int x = c->left; x < c->left + c->width && valid; ++x)
		{
			for(int y = c->top; y < c->top + c->height && valid; ++y)
			{
				if(fabric[x * 1000 + y] != c->id)
					valid = false;
			}
		}

		if(valid)
			break;
	}


	printf("Winner: %i\n", c->id);
	free(fabric);
	free(claims);

	//*/
}

void day04()
{
	FILE* fin;
	fopen_s(&fin, "input_day04.txt", "r");

	if(fin == NULL)
		return;

	// Set up lots of data
	const uint32_t LOG_COUNT = 1133;
	const uint32_t LOG_LENGTH = 45;
	char line_buf[LOG_COUNT][LOG_LENGTH] = { 0 };

	typedef uint32_t guard_id_t;
	typedef uint8_t guard_index_t;

	const uint32_t MAX_GUARD_COUNT = 128;
	guard_id_t guard_ids[MAX_GUARD_COUNT] = { 0 };
	uint32_t sleep_count[MAX_GUARD_COUNT][60] = { 0 };

	// Lambda function used by qsort to order the logs chronologically
	auto sort_logs_by_time = [](const void*e1, const void*e2) -> int
	{
		struct log_time { int32_t year, month, day, hour, minute; };
		log_time a, b;

		sscanf_s((const char*)e1, "[%d-%d-%d %d:%d]", &a.year, &a.month, &a.day, &a.hour, &a.minute);
		sscanf_s((const char*)e2, "[%d-%d-%d %d:%d]", &b.year, &b.month, &b.day, &b.hour, &b.minute);

		if(a.year < b.year) return -1;
		else if(a.year == b.year)
		{
			if(a.month < b.month) return -1;
			else if(a.month == b.month)
			{
				if(a.day < b.day) return -1;
				else if(a.day == b.day)
				{
					if(a.hour < b.hour) return -1;
					else if(a.hour == b.hour)
					{
						if(a.minute < b.minute) return -1;
						else if(a.minute == b.minute) return 0;
					}
				}
			}
		}
		return 1;
	};

	// Lambda function used to turn a guard id into an index in our array (a cheap mapping function)
	auto get_guard_index_from_id = [&guard_ids, MAX_GUARD_COUNT](guard_id_t guard_id) -> guard_index_t
	{
		for(guard_index_t i = 0; i < MAX_GUARD_COUNT; ++i)
		{
			if(guard_ids[i] == guard_id)
			{
				return i;
			}
			if(guard_ids[i] == 0)
			{
				guard_ids[i] = guard_id;
				return i;
			}
		}
		return -1;
	};

	int i = 0;
	while(fgets(line_buf[i++], LOG_LENGTH, fin)) {}
	fclose(fin);

	qsort(line_buf, LOG_COUNT, LOG_LENGTH, sort_logs_by_time);

	/* Part 1

	struct
	{
		uint32_t sleep = 0;
		guard_id_t guard_index = 0;
	} result;

	for(uint32_t i = 0; i < LOG_COUNT;)
	{
		guard_id_t guard, tmp;
		sscanf_s(line_buf[i], "[%*d-%*d-%*d %*d:%*d] Guard #%d begins shift\n", &guard);
		guard = get_guard_index_from_id(guard);

		++i; // move to the next line

		while(true)
		{
			if(sscanf_s(line_buf[i], "[%*d-%*d-%*d %*d:%*d] Guard #%d begins shift\n", &tmp) != 0)
			{
				int32_t sleep = 0;
				for(int i = 0; i < 60; ++i)
					sleep += sleep_count[guard][i];

				if(sleep > result.sleep)
				{
					result.sleep = sleep;
					result.guard_index = guard;
				}

				break;
			}

			int32_t start_time, end_time;
			sscanf_s(line_buf[i++], "[%*d-%*d-%*d %*d:%d]", &start_time);
			sscanf_s(line_buf[i++], "[%*d-%*d-%*d %*d:%d]", &end_time);

			for(int i = start_time; i < end_time; ++i)
				sleep_count[guard][i]++;
		}
	}

	uint8_t max_minute_index = 0;
	for(int i = 1; i < 60; ++i)
	{
		if(sleep_count[result.guard_index][i] > sleep_count[result.guard_index][max_minute_index])
			max_minute_index = i;
	}

	int32_t result = guard_ids[result.guard_index] * max_minute_index;
	printf("%d\n", result);

	/*/

	struct
	{
		uint32_t sleep = 0;
		guard_id_t guard_index = 0;
		uint8_t minute_index = 0;
	} result;

	for(uint32_t i = 0; i < LOG_COUNT;)
	{
		guard_id_t guard, tmp;
		sscanf_s(line_buf[i], "[%*d-%*d-%*d %*d:%*d] Guard #%d begins shift\n", &guard);
		guard = get_guard_index_from_id(guard);

		++i; // move to the next line

		while(true)
		{
			if(sscanf_s(line_buf[i], "[%*d-%*d-%*d %*d:%*d] Guard #%d begins shift\n", &tmp) != 0)
			{
				int32_t sleep = 0;
				for(int i = 0; i < 60; ++i)
				{
					if(sleep_count[guard][i] > result.sleep)
					{
						result.sleep = sleep_count[guard][i];

						result.guard_index = guard;
						result.minute_index = i;
					}
				}

				break;
			}

			int32_t start_time, end_time;
			sscanf_s(line_buf[i++], "[%*d-%*d-%*d %*d:%d]", &start_time);
			sscanf_s(line_buf[i++], "[%*d-%*d-%*d %*d:%d]", &end_time);

			for(int i = start_time; i < end_time; ++i)
				sleep_count[guard][i]++;
		}
	}

	int32_t r = guard_ids[result.guard_index] * result.minute_index;
	printf("%d\n", r);

	//*/
}

void day05()
{
	FILE* fin;
	fopen_s(&fin, "input_day05.txt", "r");

	if(fin == NULL)
		return;

	char result[50001];
	int i = 0;

	const int8_t DISTANCE_BETWEEN_CAPS = 'a' - 'A';

	//* Part 1

	while((result[i] = fgetc(fin)) != EOF)
	{
		if(i > 0 && 
			result[i - 1] == (result[i] - DISTANCE_BETWEEN_CAPS) || 
			result[i] == (result[i - 1] - DISTANCE_BETWEEN_CAPS))
		{
			// we have a match
			--i;
		}
		else
			++i;
	}
	result[i] = 0;

	fclose(fin);
	printf("%d\n", i - 1);

	/*/

	int smallest_result = INT_MAX;

	for(int ignore_letter = 'A'; ignore_letter < 'Z'; ++ignore_letter)
	{
		i = 0;

		while((result[i] = fgetc(fin)) != EOF)
		{
			if (result[i] == ignore_letter || result[i] == ignore_letter + DISTANCE_BETWEEN_CAPS)
				continue;

			if(i > 0 &&
				result[i - 1] == (result[i] - DISTANCE_BETWEEN_CAPS) ||
				result[i] == (result[i - 1] - DISTANCE_BETWEEN_CAPS))
			{
				// we have a match
				--i;
			}
			else
				++i;
		}

		fseek(fin, 0, SEEK_SET);
		if(i < smallest_result)
			smallest_result = i;
	}
	result[i] = 0;

	fclose(fin);
	printf("%d\n", smallest_result - 1);

	//*/
}

void day06()
{
	FILE* fin;
	fopen_s(&fin, "input_day06.txt", "r");

	if(fin == NULL)
		return;

	const uint32_t GRID_SIZE = 1000;
	const uint32_t COORDINATE_COUNT = 50;

	struct coordinate
	{
		int32_t x, y;
	} coordinates[COORDINATE_COUNT];

	for(int i = 0; i < COORDINATE_COUNT; ++i)
	{
		coordinate& c = coordinates[i];
		fscanf_s(fin, "%d, %d\n", &c.x, &c.y);
	}

	fclose(fin);

	/* Part 1

	int32_t coord_count[COORDINATE_COUNT] = { 0 };
	uint64_t ignore_flags = 0;

	for(int32_t x = 0; x < GRID_SIZE; ++x)
	{
		for(int32_t y = 0; y < GRID_SIZE; ++y)
		{
			int32_t closest_dist = INT_MAX;
			int32_t closest_coord = -1;

			for(int32_t i = 0; i < COORDINATE_COUNT; ++i)
			{
				int32_t dist = abs(coordinates[i].x - x) + abs(coordinates[i].y - y);
				if(dist < closest_dist)
				{
					closest_coord = i;
					closest_dist = dist;
				}
				else if(dist == closest_dist)
				{
					closest_coord = -1;
				}
			}

			if(closest_coord >= 0)
			{
				coord_count[closest_coord]++;

				if(x == 0 || y == 0 || x == GRID_SIZE - 1 || y == GRID_SIZE - 1)
					ignore_flags |= 1 << closest_coord;
			}
		}
	}

	int32_t max_area = 0;
	for(int32_t i = 0; i < COORDINATE_COUNT; ++i)
	{
		if (ignore_flags & (1 << i))
			continue;

		if(coord_count[i] > max_area)
			max_area = coord_count[i];
	}

	printf("Max area: %d\n", max_area);

	/*/
	
	const uint32_t MAX_DISTANCE = 10000;

	int32_t region_size = 0;

	for(int32_t x = 0; x < GRID_SIZE; ++x)
	{
		for(int32_t y = 0; y < GRID_SIZE; ++y)
		{
			int32_t total_distance = 0;

			for(int32_t i = 0; i < COORDINATE_COUNT; ++i)
			{
				total_distance += abs(coordinates[i].x - x) + abs(coordinates[i].y - y);
			}

			if(total_distance < MAX_DISTANCE)
				++region_size;
		}
	}

	printf("Max area: %d\n", region_size);

	//*/
}

void day07()
{
	FILE* fin;
	fopen_s(&fin, "input_day07.txt", "r");

	const uint32_t ALPHABET_SIZE = 'Z' - 'A' + 1; // probably won't change anytime soon...

	if(fin == NULL)
		return;

	struct step
	{
		char requirements[ALPHABET_SIZE] = { 0 };
		int32_t req_count = 0;
	} steps[ALPHABET_SIZE];

	while (!feof(fin))
	{
		struct {
			char id, requirement;
		} line;

		fscanf_s(fin, "Step %c must be finished before step %c can begin.\n", &line.requirement, 1, &line.id, 1);

		step& s = steps[line.id - 'A'];
		s.requirements[s.req_count++] = line.requirement - 'A';
	}
	fclose(fin);

	/* Part 1

	char completion_order[ALPHABET_SIZE + 1] = { 0 };
	uint32_t completed_steps = 0;
	uint8_t current_step = 0;

	while(completed_steps != (1 << ALPHABET_SIZE) - 1)
	{
		for(int i = 0; i < ALPHABET_SIZE; ++i) 
		{
			// Make sure we didn't already do this step
			if (completed_steps & (1 << i))
				continue;
			
			step& s = steps[i];

			bool ready = true;
			for(int j = 0; j < s.req_count && ready; ++j)
			{
				if(!(completed_steps & (1 << s.requirements[j])))
					ready = false;
			}

			if(ready)
			{
				completion_order[current_step++] = i + 'A';
				completed_steps |= (1 << i);
				break; // go back to the top to make sure we stay in alphabetical order
			}
		}
	}

	printf("Order: %s\n", completion_order);

	/*/

	const uint32_t WORKER_COUNT = 5;
	struct worker_status
	{
		char id = -1;
		unsigned char time_remaining = 0;
	} workers[WORKER_COUNT];

	uint32_t completed_steps = 0,
		active_steps = 0,
		time_taken = 0;

	while(completed_steps != (1 << ALPHABET_SIZE) - 1)
	{
		bool ticked_time = false;

		// drain time remaining
		for(uint32_t i = 0; i < WORKER_COUNT; ++i)
		{
			if(workers[i].id >= 0)
			{
				// If we completed this job, mark it as done.
				if(--workers[i].time_remaining == 0)
				{
					completed_steps |= (1 << workers[i].id);
					workers[i].id = -1;
				}

				if(!ticked_time)
				{
					ticked_time = true;
					++time_taken;
				}
			}
		}

		// find available jobs
		char available_jobs[ALPHABET_SIZE];
		int32_t available_job_count = 0;

		for(int i = 0; i < ALPHABET_SIZE; ++i)
		{
			// skip if we already did this step
			if (completed_steps & (1 << i) || active_steps & (1 << i))
				continue;

			bool ready = true;
			for(int j = 0; j < steps[i].req_count && ready; ++j)
			{
				if(!(completed_steps & (1 << steps[i].requirements[j])))
					ready = false;
			}

			if(ready)
				available_jobs[available_job_count++] = i;
		}

		// assign jobs
		for(int i = 0; i < available_job_count; ++i)
		{
			for(int j = 0; j < WORKER_COUNT; ++j)
			{
				if (workers[j].id >= 0)
					continue;

				active_steps |= (1 << available_jobs[i]);
				workers[j].id = available_jobs[i];
				workers[j].time_remaining = 61 + available_jobs[i];
				break;
			}
		}
	}

	printf("Total time: %d\n", time_taken);

	//*/
}

void day08()
{
	FILE* fin;
	fopen_s(&fin, "input_day08.txt", "r");

	if(fin == NULL)
		return;

	auto get_metadata_sum = [fin](auto& get_metadata_sum) -> int32_t
	{
		int32_t child_count, metadata_count, tmp, result = 0;

		fscanf_s(fin, "%d %d ", &child_count, &metadata_count);
		for(int32_t i = 0; i < child_count; ++i)
			result += get_metadata_sum(get_metadata_sum);

		for(int32_t i = 0; i < metadata_count; ++i)
		{
			fscanf_s(fin, "%d ", &tmp);
			result += tmp;
		}

		return result;
	};

	auto get_value = [fin](auto& get_value) -> int32_t
	{
		const int32_t MAX_CHILD_COUNT = 8;

		int32_t child_count, metadata_count, tmp, value = 0;
		fscanf_s(fin, "%d %d ", &child_count, &metadata_count);

		if(child_count == 0)
		{
			for(int32_t i = 0; i < metadata_count; ++i)
			{
				fscanf_s(fin, "%d ", &tmp);
				value += tmp;
			}
		}
		else
		{
			int32_t child_values[MAX_CHILD_COUNT];
			for(int32_t i = 0; i < child_count; ++i)
			{
				child_values[i] = get_value(get_value);
			}

			for(int32_t i = 0; i < metadata_count; ++i)
			{
				fscanf_s(fin, "%d ", &tmp);

				if (tmp > 0 && tmp <= child_count)
					value += child_values[tmp - 1];
			}
		}

		return value;
	};

	printf("Part 1: %d\n", get_metadata_sum(get_metadata_sum));
	fseek(fin, 0, SEEK_SET);
	printf("Part 2: %d\n", get_value(get_value));
	fclose(fin);
}

void day09()
{
	FILE* fin;
	fopen_s(&fin, "input_day09.txt", "r");

	if(fin == NULL)
		return;

	struct node
	{
		node *prev = nullptr, *next = nullptr;
		uint64_t val = 0;
	};

	int32_t alloc_count = 0;
	
	auto add_node = [&alloc_count](node* r, uint32_t d) -> node*
	{
		node* n = new node{ r, r->next, d };
		r->next->prev = n;
		r->next = n;
		++alloc_count;
		return n;
	};

	auto rem_node = [&alloc_count](node*& t) -> node*
	{
		node* r = t->next;
		t->next->prev = t->prev == t ? nullptr : t->prev;
		t->prev->next = t->next == t ? nullptr : t->next;

		delete t; t = nullptr;
		--alloc_count;
		return r;
	};

	node* root = new node();
	root->next = root;
	root->prev = root;

	const uint32_t MAGIC_NUMBER = 23;
	uint64_t marble_count, player_count;
	fscanf_s(fin, "%llu players; last marble is worth %llu points", &player_count, &marble_count);
	fclose(fin);

	++marble_count;

	uint64_t* player_scores = (uint64_t*)calloc(player_count, sizeof(uint64_t));
	uint64_t current_player = 0;
	for(int i = 1; i < marble_count; ++i)
	{
		current_player = (current_player + 1) % player_count;

		if(i % MAGIC_NUMBER == 0)
		{
			// do something special
			uint64_t score_value = i;

			root = root->prev->prev->prev->prev->prev->prev->prev;
			score_value += root->val;
			root = rem_node(root);

			player_scores[current_player] += score_value;
		}
		else
		{
			root = add_node(root->next, i);
		}
	}

	uint64_t max_score = 0;
	for(uint64_t i = 0; i < player_count; ++i)
	{
		if(player_scores[i] > max_score)
			max_score = player_scores[i];
	}

	while(root != nullptr)
		root = rem_node(root);

	printf("Max score: %llu\n", max_score);
}

void day10()
{
	FILE* fin;
	fopen_s(&fin, "input_day10.txt", "r");

	if(fin == NULL)
		return;

	const int32_t MAX_POINTS = 365;
	struct light_point
	{
		int32_t pos_x, pos_y, vel_x, vel_y;
	};
	
	light_point* lights_a = (light_point*)malloc(sizeof(light_point) * MAX_POINTS);
	light_point* lights_b = (light_point*)malloc(sizeof(light_point) * MAX_POINTS);

	for (int32_t i = 0; i < MAX_POINTS; ++i)
		fscanf_s(fin, "position = <%d, %d> velocity = <%d, %d>\n",
			&lights_a[i].pos_x,
			&lights_a[i].pos_y,
			&lights_a[i].vel_x,
			&lights_a[i].vel_y);

	fclose(fin);

	memcpy(lights_b, lights_a, sizeof(light_point) * MAX_POINTS);

	light_point *cur = lights_a, *prev = lights_b;
	int32_t min_x, max_x, min_y, max_y;
	int32_t step_count = 0;

	auto swap_light_buffers = [&cur, &prev, &step_count] { std::swap(cur, prev); ++step_count; };

	int64_t prev_dispersion = INT_MAX;
	while (true)
	{
		// Reset our min/max's for this loop
		min_x = INT_MAX;
		max_x = INT_MIN;
		min_y = INT_MAX;
		max_y = INT_MIN;

		// increment every point ( checking min_x and max_x along the way)
		for(int32_t i = 0; i < MAX_POINTS; ++i)
		{
			cur[i].pos_x += cur[i].vel_x;
			cur[i].pos_y += cur[i].vel_y;

			min_x = min(min_x, cur[i].pos_x);
			min_y = min(min_y, cur[i].pos_y);
			max_x = max(max_x, cur[i].pos_x);
			max_y = max(max_y, cur[i].pos_y);
		}

		// calculate dispersion from the min_x and max_x from this loop
		int64_t current_dispersion = max_x - min_x;

		// if current dispersion is LESS than previous, we're moving into the shape we want
		if(current_dispersion <= prev_dispersion)
		{
			// swap the buffers and continue.
			prev_dispersion = current_dispersion;
			swap_light_buffers();
		}
		else
		{
			// the previous buffer holds the shape we want to display. break.
			break;
		}
	}

	// Part 1
	HANDLE HStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD tmp;
	COORD write_coord;
	for(int32_t i = 0; i < MAX_POINTS; ++i)
	{
		write_coord.X = prev[i].pos_x - min_x;
		write_coord.Y = prev[i].pos_y - min_y;

		WriteConsoleOutputCharacter(HStdHandle, "X", 1, write_coord, &tmp);
	}

	// Part 2
	// I have no idea why I need to divide step_count by 2????
	printf("Seconds: %d\n", step_count / 2);

	free(lights_a);
	free(lights_b);
}

void day11()
{
	const int32_t SERIAL_NUMBER = 6303;
	const uint32_t GRID_SIZE = 300;
	const int32_t MIN_SOLUTION_SIZE = 1;
	const int32_t MAX_SOLUTION_SIZE = GRID_SIZE;

	const int32_t GRID_SIZE_P1 = GRID_SIZE + 1;

	// This could exist on the stack for 300x300, but I wanted to be able to increase the grid size later
	int32_t *sum_area_grid = (int32_t*)calloc(GRID_SIZE_P1 * GRID_SIZE_P1, sizeof(int32_t));

	auto calc_power_level = [SERIAL_NUMBER](int32_t x, int32_t y) -> int32_t
	{
		int32_t rack_id = x + 10;
		return (((((rack_id * y) + SERIAL_NUMBER) * rack_id) / 100) % 10) - 5;
	};

	auto address = [GRID_SIZE](int32_t x, int32_t y) -> int32_t
	{
		return x * GRID_SIZE + y;
	};

	struct { int32_t x, y, s = 1, power = INT_MIN; } result;

	// Fill the grid with values and fill the summed-area table
	for(int32_t x = 1; x < GRID_SIZE_P1; ++x)
	{
		for(int32_t y = 1; y < GRID_SIZE_P1; ++y)
		{
			int32_t v = calc_power_level(x, y);
			int32_t c = sum_area_grid[address(x, y - 1)];
			int32_t a = sum_area_grid[address(x - 1, y - 1)];
			int32_t b = sum_area_grid[address(x - 1, y)];

			int32_t d = v + b + c - a;
			sum_area_grid[address(x, y)] = d;
		}
	}

	// Because of cache coherency, it's actually faster to loop through a second time...
	for(int32_t s = MIN_SOLUTION_SIZE; s <= MAX_SOLUTION_SIZE; ++s)
	{
		for(int32_t x = s; x < GRID_SIZE; ++x)
		{
			for(int32_t y = s; y < GRID_SIZE; ++y)
			{
				int32_t
					low_x = x - s,
					low_y = y - s;

				int32_t a = sum_area_grid[address(low_x, low_y)];
				int32_t c = sum_area_grid[address(low_x, y)];
				int32_t b = sum_area_grid[address(x, low_y)];
				int32_t d = sum_area_grid[address(x, y)];

				int32_t sum = d - b - c + a;
				if(sum > result.power)
				{
					result.power = sum;
					result.x = x - s + 1;
					result.y = y - s + 1;
					result.s = s;
				}
			}
		}
	}

	printf("Result: %d,%d,%d\n", result.x, result.y, result.s);
	free(sum_area_grid);
}

void day12()
{
	FILE* fin;
	fopen_s(&fin, "input_day12.txt", "r");

	const uint32_t BUFFER_SIZE = 2048;
	const uint32_t RULES_COUNT = 32;
	const uint32_t RULES_SIZE = 5;
	const uint32_t INITIAL_ZERO = BUFFER_SIZE / 2;
	const uint64_t GENERATION_COUNT = 50000000000ull; // These might be specific to my input data?
	const uint64_t GENERATION_STABILITY_POINT = 195;  // These might be specific to my input data?

	if(fin == NULL)
		return;

	bool buffer_a[BUFFER_SIZE] = { 0 }, buffer_b[BUFFER_SIZE] = { 0 };
	bool *active = buffer_a, *previous = buffer_b;

	struct rule
	{
		bool reqs[RULES_SIZE];
		bool result;

		bool matches(bool* area) const
		{
			for(int32_t i = 0; i < RULES_SIZE; ++i)
			{
				if(area[i] != reqs[i])
					return false;
			}
			return true;
		}
	} rules[RULES_COUNT];

	char input_buffer[BUFFER_SIZE], tmp;
	fscanf_s(fin, "initial state: %s\n", input_buffer, BUFFER_SIZE);
	for(uint32_t i = 0; i < BUFFER_SIZE - INITIAL_ZERO; ++i)
		buffer_a[i + INITIAL_ZERO] = buffer_b[i + INITIAL_ZERO] = input_buffer[i] == '#';

	for(int32_t i = 0; i < RULES_COUNT; ++i)
	{
		fscanf_s(fin, "%s => %c", input_buffer, BUFFER_SIZE, &tmp, 1);

		for(int32_t j = 0; j < RULES_SIZE; ++j)
			rules[i].reqs[j] = input_buffer[j] == '#';
		rules[i].result = tmp == '#';
	}

	fclose(fin);

	for(uint64_t generation = 0; generation <= GENERATION_COUNT && generation < GENERATION_STABILITY_POINT; ++generation)
	{
		for(int32_t x = 0; x < BUFFER_SIZE - RULES_SIZE; ++x)
		{
			for(int32_t r = 0; r < RULES_COUNT; ++r)
			{
				if(rules[r].matches(previous + x))
					active[x + 2] = rules[r].result;
			}
		}

		std::swap(previous, active);
	}

	int64_t sum = 0;
	for(int64_t i = 0; i < BUFFER_SIZE; ++i)
		sum += active[i] * (i - (int64_t)INITIAL_ZERO);

	sum += (GENERATION_COUNT > GENERATION_STABILITY_POINT) ? (GENERATION_COUNT - GENERATION_STABILITY_POINT) * 45ull : 0;

	printf("Count: %lld\n", sum);
}

void day13()
{
	FILE* fin;
	fopen_s(&fin, "input_day13.txt", "r");

	const uint32_t X_WIDTH = 152;
	const uint32_t Y_HEIGHT = 152;
	const uint32_t CART_COUNT = 17;

	char track[Y_HEIGHT][X_WIDTH] = { 0 };

	struct cart
	{
		uint32_t y = INT_MAX, x = INT_MAX;
		uint32_t dir;
		enum D : uint32_t { LEFT, STRAIGHT, RIGHT } turn_dir = LEFT;

		void intersection_turn()
		{
			if (turn_dir == LEFT)
			{
				switch (dir)
				{
				case 'v': dir = '>'; break;
				case '^': dir = '<'; break;
				case '<': dir = 'v'; break;
				case '>': dir = '^'; break;
				}
			}
			else if (turn_dir == RIGHT)
			{
				switch (dir)
				{
				case 'v': dir = '<'; break;
				case '^': dir = '>'; break;
				case '<': dir = '^'; break;
				case '>': dir = 'v'; break;
				}
			}

			turn_dir = (D)((turn_dir + 1) % (RIGHT + 1)); 
		}

		void backslash_turn()
		{
			if (dir == '>')
				dir = 'v';
			else if (dir == '^')
				dir = '<';
			else if (dir == '<')
				dir = '^';
			else if (dir == 'v')
				dir = '>';
		}

		void forwardslash_turn()
		{
			if (dir == '>')
				dir = '^';
			else if (dir == '^')
				dir = '>';
			else if (dir == '<')
				dir = 'v';
			else if (dir == 'v')
				dir = '<';
		}

	} carts[CART_COUNT];

	auto sort_carts = [](const void* a, const void* b) -> int32_t
	{
		const cart *l = (const cart*)a;
		const cart *r = (const cart*)b;

		if (l->y < r->y || (l->y == r->y && l->x < r->x)) return -1;
		else if (l->y == r->y && l->x == r->x) return 0;
		else return 1;
	};

	if (fin == NULL)
		return;

	uint32_t cart_num = 0;
	for (int32_t x = 0, y = 0; !feof(fin); x = 0, ++y)
	{
		char line_buffer[X_WIDTH];
		fgets(line_buffer, X_WIDTH, fin);

		char c;
		while (c = line_buffer[x],
			c != '\n' && c!= 0)
		{
			if (c == '^' || c == 'v' || c == '<' || c == '>')
			{
				carts[cart_num].x = x;
				carts[cart_num].y = y;
				carts[cart_num].dir = c;
				++cart_num;

				switch (c)
				{
				case 'v':
				case '^': track[y][x++] = '|'; break;
				case '<':
				case '>': track[y][x++] = '-'; break;
				}
			}
			else
			{
				track[y][x++] = c;
			}
		}
	}
	fclose(fin);

	struct { int32_t tick = 0, x, y, crash_count = 0; } result;
	bool collision_occurred = false;

	HANDLE HStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD tmp;
	COORD write_coord;

	while (!collision_occurred)
	{
		++result.tick;
		qsort(carts, CART_COUNT, sizeof(cart), sort_carts);

		//* Part 2
		if (cart_num == 1)
		{
			result.x = carts[0].x;
			result.y = carts[0].y;
			break;
		} /**/

		// Update all of the carts
		for (int32_t i = 0; i < cart_num && !collision_occurred; ++i)
		{
			cart& c = carts[i];

			// Make sure this is a valid cart
			if (c.x == INT_MAX || c.y == INT_MAX)
				continue;

			// Tick actual movement
			switch (carts[i].dir)
			{
			case 'v': c.y++; break;
			case '^': c.y--; break;
			case '<': c.x--; break;
			case '>': c.x++; break;
			}

			// Check for turns
			switch (track[c.y][c.x])
			{
			case '+': c.intersection_turn(); break;
			case '\\': c.backslash_turn(); break;
			case '/': c.forwardslash_turn(); break;
			}

			// Check all carts to see if there's a collision
			for (int32_t j = 0; j < cart_num; ++j)
			{
				if (i == j)
					continue;

				/* Part 1
				if (carts[j].x == c.x && carts[j].y == c.y)
				{
					result.x = c.x;
					result.y = c.y;
					collision_occurred = true;
					break;
				}

				/*/// Part 2
				if (carts[j].x == c.x && carts[j].y == c.y)
				{
					carts[j].x = carts[j].y = INT_MAX;
					c.x = c.y = INT_MAX;
					result.crash_count++;
					break;
				}

				//*/
			}
		}

		cart_num -= result.crash_count * 2;
		result.crash_count = 0;

		//* Draw the track
		for (int32_t y = 0; y < Y_HEIGHT; ++y)
		{
			for (int32_t x = 0; x < X_WIDTH; ++x)
			{
				char output = track[y][x];
				WORD color = 15;

				for (int32_t i = 0; i < cart_num; ++i) 
				{
					if (carts[i].y == y && carts[i].x == x) 
					{ 
						output = carts[i].dir;

						switch (carts[i].turn_dir)
						{
						case cart::LEFT: color = FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
						case cart::STRAIGHT: color = FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
						case cart::RIGHT: color = FOREGROUND_RED | FOREGROUND_INTENSITY; break;
						}
						break;
					} 
				}

				write_coord = { (SHORT)x, (SHORT)y };
				WriteConsoleOutputAttribute(HStdHandle, &color, 1, write_coord, &tmp);
				WriteConsoleOutputCharacter(HStdHandle, &output, 1, write_coord, &tmp);
			}
		}

		//Sleep(50); /**/
	}

	printf("Collision occurred at second %d @ %d,%d\n", result.tick, result.x, result.y);
	CloseHandle(HStdHandle);
}

void day14()
{
	const int32_t PUZZLE_INPUT = 909441;
	const int32_t PUZZLE_INPUT_ARR[] = { 9,0,9,4,4,1 };
	const int32_t PUZZLE_INPUT_COUNT = sizeof(PUZZLE_INPUT_ARR) / sizeof(PUZZLE_INPUT_ARR[0]);
	const int32_t * const PUZZLE_INPUT_END = PUZZLE_INPUT_ARR + PUZZLE_INPUT_COUNT;
	const uint32_t FIRST_VAL = 3;
	const uint32_t SECOND_VAL = 7;

	struct vec
	{
		const int32_t DEFAULT_CAPACITY = 32;

		int32_t *buf = (int32_t*)malloc(sizeof(int32_t) * DEFAULT_CAPACITY);
		int32_t size = 0, capacity = DEFAULT_CAPACITY;

		void push_back(int32_t v)
		{
			while (size >= capacity)
				buf = (int32_t*)realloc(buf, sizeof(int32_t) * (capacity *= 2));

			buf[size++] = v;
		}

		void destruct()
		{
			free(buf);
			size = capacity = 0;
		}

	} recipes;

	int32_t elf_1_index = 0;
	int32_t elf_2_index = 1;

	auto choose_active_recipe = [&recipes](int32_t i) -> int32_t
	{
		return (recipes.buf[i] + 1 + i) % recipes.size;
	};

	auto calculate_new_recipe = [&recipes](int32_t elf_1, int32_t elf_2)
	{
		char new_recipe[16] = { 0 }, 
			*c = new_recipe;

		sprintf_s(new_recipe, 16, "%d", recipes.buf[elf_1] + recipes.buf[elf_2]);
		while (*c != 0)
		{
			recipes.push_back((*c++) - '0');
		}
	};

	recipes.push_back(FIRST_VAL);
	recipes.push_back(SECOND_VAL);

	/* Part 1
	while (recipes.size < PUZZLE_INPUT + 11)
	{
		calculate_new_recipe(elf_1_index, elf_2_index);

		elf_1_index = choose_active_recipe(elf_1_index);
		elf_2_index = choose_active_recipe(elf_2_index);
	}

	int32_t *start_addr = recipes.buf + PUZZLE_INPUT;
	for (int32_t i = 0; i < 10; ++i)
		printf("%d", *(start_addr++));
	printf("\n");

	/*///Part 2

	int32_t const* needle = PUZZLE_INPUT_ARR;
	int32_t i = 0;

	while (needle != PUZZLE_INPUT_END)
	{
		calculate_new_recipe(elf_1_index, elf_2_index);

		for (; i < recipes.size; ++i)
		{
			if (recipes.buf[i] == *needle)
			{
				// all is good, we're matching!
				++needle;

				// If we're at the end, stop checking
				if (needle == PUZZLE_INPUT_END)
					break;
			}
			else
			{
				// if we failed to match partway through, we need to back up i to catch repeated characters
				i -= (PUZZLE_INPUT_ARR - needle);
				needle = PUZZLE_INPUT_ARR;
			}
		}

		elf_1_index = choose_active_recipe(elf_1_index);
		elf_2_index = choose_active_recipe(elf_2_index);
	}

	int32_t index = i - PUZZLE_INPUT_COUNT + 1;
	printf("Recipes: %d\n", index);

	//*/

	recipes.destruct();
}

void day15()
{

}
