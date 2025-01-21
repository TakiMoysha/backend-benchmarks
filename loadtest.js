import http from "k6/http";
import { check } from "k6";

export const options = {
  scenarios: {
    constant_request_rate: {
      executor: "constant-arrival-rate",
      rate: 30000,
      timeUnit: "1s",
      duration: "1m",
      preAllocatedVUs: 2000,
      maxVUs: 8000
    }
  }
}

export default function () {
  const res = http.get(`http://127.0.0.1:8000/api/orders`);
  check(res, { "status was 200": (r) => r.status == 200 });
}
