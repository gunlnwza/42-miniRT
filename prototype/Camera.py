from Vector3 import Vector3

class Camera:
	def __init__(self, center, image_size):
		image_width, image_height = image_size
		focal_length = 1
		viewport_height = 2
		viewport_width = viewport_height * (image_width / image_height)

		viewport_u = Vector3(viewport_width, 0, 0)
		viewport_v = Vector3(0, viewport_height, 0)
		viewport_upper_left = center - Vector3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2

		self.center = center
		self.pixel_delta_u = viewport_u / image_width
		self.pixel_delta_v = viewport_v / image_height
		self.pixel00_loc = viewport_upper_left + 0.5 * (self.pixel_delta_u + self.pixel_delta_v)
